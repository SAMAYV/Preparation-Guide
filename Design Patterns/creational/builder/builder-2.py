from abc import ABC, abstractmethod

class Student:
    def __init__(self):
        self.name = None
        self.roll_no = None
        self.age = None
        self.branch = None
        self.subjects = []
        self.email = None

    def __str__(self):
        return (
            f"Student name: {self.name}," + 
            f"roll no: {self.roll_no}," + 
            f"age: {self.age}," + 
            f"branch: {self.branch}," + 
            f"subjects: {self.subjects}," + 
            f"email: {self.email}"
        )

class StudentBuilder(ABC):
    def __init__(self):
        self.reset()

    @abstractmethod
    def set_subjects(self, subjects) -> 'StudentBuilder':
        pass

    def reset(self):
        self.student = Student()
        return self
    
    def build(self):
        return self.student

    def set_name(self, name):
        self.student.name = name
        return self

    def set_roll_no(self, roll_no):
        self.student.roll_no = roll_no
        return self

    def set_age(self, age):
        self.student.age = age
        return self

    def set_branch(self, branch):
        self.student.branch = branch
        return self

    def add_subject(self, subject):
        self.student.subjects.append(subject)
        return self

    def set_email(self, email):
        self.student.email = email
        return self

class EngineeringStudentBuilder(StudentBuilder):
    def set_subjects(self, subjects):
        self.student.subjects = subjects
        return self

class MedicalStudentBuilder(StudentBuilder):
    def set_subjects(self, subjects):
        self.student.subjects = subjects
        return self

class StudentDirector:
    def build_engineering_student(self, builder: StudentBuilder):
        return builder.reset()\
            .set_name("John")\
            .set_roll_no(1)\
            .set_age(20)\
            .set_branch("CSE")\
            .set_subjects(["Operating Systems", "Data Structures", "Algorithms"])\
            .set_email("john@tessell.com")\
            .build()
    
    def build_medical_student(self, builder: StudentBuilder):
        return builder.set_name("Jane")\
            .set_roll_no(2)\
            .set_age(20)\
            .set_branch("Medicine")\
            .set_subjects(["Anatomy", "Physiology", "Pharmacology"])\
            .set_email("jane@tessell.com")\
            .build()
    
class Application:
    def main(self):
        director = StudentDirector()
        engineering_builder = EngineeringStudentBuilder()
        engineering_student = director.build_engineering_student(engineering_builder)
        print(f"Engineering Student: {str(engineering_student)}\n")

        medical_builder = MedicalStudentBuilder()
        medical_student = director.build_medical_student(medical_builder)
        print(f"Medical Student: {str(medical_student)}")

if __name__ == "__main__":
    app = Application()
    app.main()
