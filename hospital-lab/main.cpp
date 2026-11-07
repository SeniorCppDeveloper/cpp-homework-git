#include <iostream>
#include <string>
#include <vector>
#include <utility>

enum class Department {
    Therapy,
    Surgery,
    Cardiology,
    Unknown
};

enum class PatientState {
    InQueue,
    InTreatment,
    Discharged
};

std::string departmentToString(Department d) {
    switch (d) {
        case Department::Therapy:    return "Терапия";
        case Department::Surgery:    return "Хирургия";
        case Department::Cardiology: return "Кардиология";
        default:                     return "Неизвестно";
    }
}

std::string stateToString(PatientState s) {
    switch (s) {
        case PatientState::InQueue:     return "В очереди";
        case PatientState::InTreatment: return "Лечится";
        case PatientState::Discharged:  return "Выписан";
        default:                        return "Неизвестно";
    }
}

class Patient {
protected:
    std::string name;
    int age;
    Department dept;
    PatientState state;
public:
    Patient(std::string name, int age, Department dept)
        : name(std::move(name)), age(age), dept(dept),
          state(PatientState::InQueue) {}
    virtual ~Patient() = default;
    void setState(PatientState s) { state = s; }
    virtual std::string getDescription() const {
        return "Пациент: " + name +
               ", возраст: " + std::to_string(age) +
               ", отделение: " + departmentToString(dept) +
               ", состояние: " + stateToString(state);
    }
};

class ChildPatient : public Patient {
    std::string parentName;

public:
    ChildPatient(std::string name, int age, Department dept, std::string parentName)
        : Patient(std::move(name), age, dept),
          parentName(std::move(parentName)) {}
    std::string getDescription() const override {
        return "Ребёнок: " + name +
               ", возраст: " + std::to_string(age) +
               ", отделение: " + departmentToString(dept) +
               ", состояние: " + stateToString(state) +
               ", родитель: " + parentName;
    }
};

int main() {
    Patient adult("Иван Петров", 35, Department::Surgery);
    ChildPatient child("Маша Иванова", 8, Department::Therapy, "Ольга Иванова");
    std::cout << adult.getDescription() << "\n";
    std::cout << child.getDescription() << "\n";
    adult.setState(PatientState::InTreatment);
    std::cout << adult.getDescription() << "\n";
    return 0;
}
