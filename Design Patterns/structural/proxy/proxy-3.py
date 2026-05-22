from abc import ABC, abstractmethod

class UserType:
    ADMIN = 1
    MANAGER = 2
    EMPLOYEE = 3

class EmployeeDao(ABC):
    @abstractmethod
    def create(self, user, employee):
        pass
    @abstractmethod
    def update(self, user, employee):
        pass
    @abstractmethod
    def delete(self, user, employeeId):
        pass
    @abstractmethod
    def find(self, user, employeeId) -> str:
        pass

# DaoImpl will interact with database
class EmployeeDaoImpl(EmployeeDao):
    def create(self, user, employee):
        print(f"Creating employee {employee} in database")
    
    def update(self, user, employee):
        print(f"Updating employee {employee} in database")
    
    def delete(self, user, employeeId):
        print(f"Deleting employee {employeeId} from database")
    
    def find(self, user, employeeId):
        print(f"Finding employee {employeeId} in database")
        return "Employee"

# Log all the operations before and after the database operation
class EmployeeDaoLoggingProxy(EmployeeDao):
    def __init__(self, employeeDao: EmployeeDao):
        self.employeeDao = employeeDao
    
    def create(self, user, employee):
        print(f"[LOG] User {user.type} attempting to create employee {employee}")
        result = self.employeeDao.create(user, employee)
        print(f"[LOG] Employee {employee} created successfully")
        return result
    
    def update(self, user, employee):
        print(f"[LOG] User {user.type} attempting to update employee {employee}")
        self.employeeDao.update(user, employee)
        print(f"[LOG] Employee {employee} updated successfully")
    
    def delete(self, user, employeeId):
        print(f"[LOG] User {user.type} attempting to delete employee {employeeId}")
        self.employeeDao.delete(user, employeeId)
        print(f"[LOG] Employee {employeeId} deleted successfully")

    def find(self, user, employeeId):
        print(f"[LOG] User {user.type} attempting to find employee {employeeId}")
        result = self.employeeDao.find(user, employeeId)
        print(f"[LOG] Employee {employeeId} found successfully")
        return result
    
class EmployeeDaoAuthProxy(EmployeeDao):
    def __init__(self, employeeDao: EmployeeDao):
        self.employeeDao = employeeDao
    
    def create(self, user, employee):
        if user.type != UserType.ADMIN:
            raise Exception("Only admin can create employee")
        return self.employeeDao.create(user, employee)
    
    def update(self, user, employee):
        if user.type != UserType.ADMIN:
            raise Exception("Only admin can update employee")
        self.employeeDao.update(user, employee)
    
    def delete(self, user, employeeId):
        if user.type != UserType.ADMIN:
            raise Exception("Only admin can delete employee")
        self.employeeDao.delete(user, employeeId)

    def find(self, user, employeeId):
        if user.type != UserType.ADMIN and user.type != UserType.MANAGER:
            raise Exception("Only admin and manager can find employee")
        return self.employeeDao.find(user, employeeId)

class User:
    def __init__(self, type):
        self.type = type

class Application:
    def main(self):
        # Layer 1: Real implementation
        employeeDaoImpl = EmployeeDaoImpl()
        
        # Layer 2: Auth proxy wraps the real implementation
        employeeDaoAuth = EmployeeDaoAuthProxy(employeeDaoImpl)
        
        # Layer 3: Logging proxy wraps the auth proxy
        employeeAuthLoggingDao = EmployeeDaoLoggingProxy(employeeDaoAuth)
        
        print("=== Admin creating employee ===")
        employeeAuthLoggingDao.create(User(UserType.ADMIN), "Employee 1")
        
        print("\n=== Manager trying to create employee ===")
        try:
            employeeAuthLoggingDao.create(User(UserType.MANAGER), "Employee 2")
        except Exception as e:
            print(f"Error: {e}")

if __name__ == "__main__":
    app = Application()
    app.main()
