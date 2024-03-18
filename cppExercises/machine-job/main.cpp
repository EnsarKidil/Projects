#include <iostream>

class Job {
public:
    int Job_ID;
    int Job_Duration;

    void print() {
        std::cout << "Job_ID: " << Job_ID << ", Job Duration: " << Job_Duration << std::endl;
    }
};

class Machine {
public:
    Job Assigned_jobs_array[10] = {};
    int Job_counter;
    int Total_time;

    Machine() {
        Job_counter = 0;
        Total_time = 0;
    }

    void print() {
        for(int i = 0; i < Job_counter; i++) {
            Assigned_jobs_array[i].print();
        }
        std::cout << "Total Time: " << Total_time << std::endl;
    }

    void operator[](Job job) {

        if(Job_counter == 10) {
            std::cout << "This machine already reached maximum capacity" << std::endl;
        }

        Assigned_jobs_array[Job_counter] = job;
        Job_counter++;
        Total_time += job.Job_Duration;
    }

};

int main() {
    Machine Machines[20]{};
    Job Jobs[50]{{101, 14}, {102, 10}, {103, 7}, {104, 6}, {105, 5}, {106 ,3}, {107, 2}};
    for(int i = 0; i < 7; i++) {

        int length = 3;
        int min = Machines[0].Total_time;
        int minIndx = 0;

        for(int j = 1; j < length; j++) {
            if(Machines[j].Total_time < min) {
                min = Machines[j].Total_time;
                minIndx = j;
            }
        }
        Machines[minIndx][Jobs[i]];
    }

    for(int i = 0; i < 3; i++) {
        Machines[i].print();
    }
}
