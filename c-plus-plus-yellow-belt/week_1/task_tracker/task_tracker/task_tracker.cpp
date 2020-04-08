#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

enum class TaskStatus {
    NEW,
    IN_PROGRESS,
    TESTING,
    DONE
};

using TasksInfo = map<TaskStatus, int>;

TaskStatus Next(TaskStatus task_status) {
    return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

class TeamTasks {
public:
    const TasksInfo& GetPersonTasksInfo(const std::string& person) const
    {
        return team_.at(person);
    }

    void AddNewTask(const string& person)
    {
        team_[person][TaskStatus::NEW]++;
    }

    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count)
    {
        TasksInfo untouched_tasks = team_[person];
        TasksInfo updated_tasks;
        const int task_done = untouched_tasks[TaskStatus::DONE];
        for (auto& current_task : untouched_tasks)
        {
            if (current_task.first != TaskStatus::DONE)
            {
                UpdateTasks(current_task.second, task_count, updated_tasks, Next(current_task.first));
            }
        }
        team_[person] = UpdatePersonTasksInfo(untouched_tasks, updated_tasks);
        RemoveZeroFields(untouched_tasks);
        RemoveZeroFields(updated_tasks);
        if (untouched_tasks[TaskStatus::DONE] == task_done) { untouched_tasks.erase(TaskStatus::DONE); }
        return tuple<TasksInfo, TasksInfo>(updated_tasks, untouched_tasks);
    }

private:
    map<string, TasksInfo> team_;
    void UpdateTasks(int& tasks_number, int& counter, TasksInfo& updated_map, TaskStatus task_status)
    {
        while (tasks_number > 0 && counter > 0)
        {
            --tasks_number;
            --counter;
            updated_map[task_status]++;
        }
    }

    TasksInfo UpdatePersonTasksInfo(TasksInfo tasks_info_1, TasksInfo tasks_info_2)
    {
        TasksInfo result;
        for (TaskStatus status = TaskStatus::NEW; static_cast<int>(status) < 4; status = Next(status))
        {
            if (tasks_info_1[status] != 0 || tasks_info_2[status] != 0)
            {
                result[status] = tasks_info_1[status] + tasks_info_2[status];
            }
        }
        return result;
    }

    void RemoveZeroFields(TasksInfo& info)
    {
        for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status))
        {
            if (info[status] == 0)
            {
                info.erase(status);
            }
        }
    }
};

void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    TasksInfo updated_tasks, untouched_tasks;

    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    cout << "Alice's tasks - 1:\t"; PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    cout << "Updated Alice's tasks:\t"; PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks:\t"; PrintTasksInfo(untouched_tasks);
    cout << "Alice's tasks - 2:\t"; PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    cout << "==========================================" << endl << endl;



    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    cout << "Updated Alice's tasks:\t"; PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks:\t"; PrintTasksInfo(untouched_tasks);
    cout << "==========================================" << endl << endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
    cout << "Updated Alice's tasks:\t"; PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks:\t"; PrintTasksInfo(untouched_tasks);
    cout << "==========================================" << endl << endl;

    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    cout << "Alice's tasks - 1:\t"; PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 2);
    cout << "Updated Alice's tasks:\t"; PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks:\t"; PrintTasksInfo(untouched_tasks);
    cout << "Alice's tasks - 2:\t"; PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    cout << "==========================================" << endl << endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
    cout << "Updated Alice's tasks:\t"; PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks:\t"; PrintTasksInfo(untouched_tasks);
    cout << "==========================================" << endl << endl;

    cout << "Alice's tasks:\t\t"; PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    cout << "==========================================" << endl << endl;
    return 0;
}