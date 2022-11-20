#include "worker.h"

void Worker::accept_connection() {
    MPI_Recv(&this->known_nodes_cnt, 1, MPI::INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    this->known_nodes_cnt++;
    delete[] this->known_nodes;
    delete[] this->known_names;
    this->known_nodes = new int[this->known_nodes_cnt];
    this->known_names = new int[this->known_nodes_cnt];
    MPI_Recv(this->known_nodes, this->known_nodes_cnt, MPI::INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(this->known_names, this->known_nodes_cnt, MPI::INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    this->known_nodes[this->known_nodes_cnt - 1] = this->rank;
    this->known_names[this->known_nodes_cnt - 1] = this->name;
}

void Worker::connect_to_next() {
    int next_rank = rand() % this->size;
    int* array_end = this->known_nodes + this->known_nodes_cnt;

    while (std::find(this->known_nodes, array_end, next_rank) != array_end) {
        next_rank = rand() % this->size;
    }

    if (this->verbose)
        std::cout << "Worker " << this->rank << " data sending to  " << next_rank << std::endl;

    MPI_Ssend(&this->known_nodes_cnt, 1, MPI::INT, next_rank, 0, MPI_COMM_WORLD);
    MPI_Ssend(this->known_nodes, this->known_nodes_cnt, MPI::INT, next_rank, 0, MPI_COMM_WORLD);
    MPI_Ssend(this->known_names, this->known_nodes_cnt, MPI::INT, next_rank, 0, MPI_COMM_WORLD);
}

void Worker::run() {
    if (this->verbose)
        std::cout << "Worker " << this->rank << " started with name " << this->name << std::endl;

    if (this->rank == 0) {
        this->known_nodes_cnt = 1;
        this->known_nodes = new int[1];
        this->known_names = new int[1];
        this->known_nodes[0] = this->rank;
        this->known_names[0] = this->name;
    }
    else {
        this->accept_connection();
    }
    if (this->known_nodes_cnt == this->size) {
        this->print_known_nodes();
    }
    else {
        this->connect_to_next();
    }
}

void Worker::print_known_nodes() {
    std::cout << "rank\tname" << std::endl;

    for (int i = 0; i < this->known_nodes_cnt; i++) {
        int name = this->known_names[i];
        int rank = this->known_nodes[i];
        std::cout << rank << '\t' << name << std::endl;
    }
}
