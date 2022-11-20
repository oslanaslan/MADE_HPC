#include "worker.h"

void Worker::run(int max_iter_cnt) {
    std::ofstream out_file;
    std::string filename = "results/res_" + std::to_string(this->rank) + ".csv"; 

    out_file.open(filename);
    out_file << "rank;step;state" << std::endl;

    this->init_state();

    for (int i = 0; i < max_iter_cnt; i++) {
        // Synchronize the ghost cells state
        this->exchange_ghost_nodes();
        this->iteration_step();
        this->print_state(i, out_file);
    }

    out_file.close();
}

void Worker::print_state(int iter, std::ofstream& out_file) {
    out_file << this->rank << ";" << iter << ";";
    // Print left ghost cell
    // out_file << this->states[0] << " ";

    for (int i = 1; i < this->state_size - 1; i++) {
        out_file << this->states[i];
    }

    // Print right ghost cell
    // out_file << " " << this->states[this->state_size - 1];
    out_file << std::endl;
}

int Worker::state_update(int left, int inner, int right) {
    // Compute current state based on Rule-110
    int res;

    switch (left * 4 + inner * 2 + right) {
        case 0:
            res = 0;
            break;
        case 1:
            res = 1;
            break;
        case 2:
            res = 1;
            break;
        case 3:
            res = 1;
            break;
        case 4:
            res = 0;
            break;
        case 5:
            res = 1;
            break;
        case 6:
            res = 1;
            break;
        case 7:
            res = 0;
            break;
        default:
            // throw std::exception("Not Implemented");
            res = -1;
            break;
    }

    return res;
}

void Worker::iteration_step() {
    // Update states
    int prev_step_value = this->states[0];

    for (int i = 1; i < this->state_size - 1; i++) {
        // We can't update inner state value on step i immediately, becouse we need it
        // for computing new value on step i+1 as it will be left cell
        // So we update i-th cell after computing i+1 cell
        int cur_step_value = this->state_update(this->states[i-1], this->states[i], this->states[i+1]);
        this->states[i-1] = prev_step_value;
        prev_step_value = cur_step_value;
    }

    this->states[this->state_size - 2] = prev_step_value;
    // Update ghost cells
    this->states[0] = this->states[1];
    this->states[this->state_size - 1] = this->states[this->state_size - 2];
}

void Worker::init_state() {
    // Initialize states
    this->states = new int[this->state_size];

    for (int i = 0; i < this->state_size; i++) {
        this->states[i] = rand() % 2;
    }

    this->states[0] = this->states[1];
    this->states[this->state_size - 1] = this->states[this->state_size - 2];
}

void Worker::exchange_ghost_nodes() {
    int left_node = this->rank == 0 ? this->size - 1 : this->rank - 1;
    int right_node = this->rank == this->size - 1 ? 0 : this->rank + 1;
    int* left_ghost_ptr = this->states;
    int* right_ghost_ptr = this->states + this->state_size - 1;
    int left_ghost_val = *left_ghost_ptr;
    int right_ghost_val = *right_ghost_ptr;
    MPI_Request left_req, right_req;

    // MPI_Isend(&left_ghost_val, 1, MPI::INT, left_node, 0, MPI_COMM_WORLD, &left_req);
    // MPI_Isend(&right_ghost_val, 1, MPI::INT, right_node, 0, MPI_COMM_WORLD, &right_req);
    if (this->rank % 2 == 0) {
        MPI_Ssend(&right_ghost_val, 1, MPI::INT, right_node, 0, MPI_COMM_WORLD);
        MPI_Recv(right_ghost_ptr, 1, MPI::INT, right_node, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Ssend(&left_ghost_val, 1, MPI::INT, left_node, 0, MPI_COMM_WORLD);
        MPI_Recv(left_ghost_ptr, 1, MPI::INT, left_node, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else {
        MPI_Recv(left_ghost_ptr, 1, MPI::INT, left_node, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Ssend(&left_ghost_val, 1, MPI::INT, left_node, 0, MPI_COMM_WORLD);
        MPI_Recv(right_ghost_ptr, 1, MPI::INT, right_node, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Ssend(&right_ghost_val, 1, MPI::INT, right_node, 0, MPI_COMM_WORLD);
    }
}