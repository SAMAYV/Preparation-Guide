"""
Proxy Design Pattern:

Principle:
    Proxy design pattern is leveraged when we need to implement a middleware between the client and the
    server. We might have multiple layers of proxies.
    In proxy design we expose the proxy to the client, and this proxy internally has the concrete class
    objects. Client makes calls through the proxy and the proxy forwards the call to the concrete class
    as per business logic. Calls might get marshalled/de-marshalled.

Use-case:
    Proxy can be used for Authentication, Authorisation, Caching, etc.

"""
from abc import ABC, abstractmethod
from enum import Enum


class Accessor(Enum):
    ADMIN = 'Admin'
    USER = 'User'


class Employee:

    def __init__(self, name, employee_id):
        self._name = name
        self._employee_id = employee_id

    def __repr__(self):
        return f"Employee({self._name}, {self._employee_id})"

    def __str__(self):
        return f"Employee ID: {self._employee_id}, Employee Name: {self._name}"

    def get_employee_id(self):
        return self._employee_id


class EmployeeDataAccessInterface(ABC):

    @abstractmethod
    def create(self, employee):
        pass

    @abstractmethod
    def delete(self, employee_id):
        pass

    @abstractmethod
    def get(self, employee_id):
        pass

    @abstractmethod
    def return_all_employees(self):
        pass


class EmployeeDataAccessObject(EmployeeDataAccessInterface):

    _list_of_employees = []

    def get(self, employee_id):
        for emp in self._list_of_employees:
            if emp.get_employee_id() == employee_id:
                print(f"Fetched employee with Employee ID: {employee_id}")
                return emp
        raise KeyError(f"No employee present with employee_id: {employee_id}")

    def create(self, employee):
        print(f"Created an employee: {employee}")
        self._list_of_employees.append(employee)

    def delete(self, employee_id):
        for emp in self._list_of_employees:
            if emp.get_employee_id() == employee_id:
                self._list_of_employees.remove(emp)
                del emp
                print(f"Deleted employee with Employee ID: {employee_id}")
                break
        else:
            raise KeyError(f"No employee present with employee_id: {employee_id}")

    def return_all_employees(self):
        return self._list_of_employees


class EmployeeDataAccessProxy(EmployeeDataAccessInterface):

    def __init__(self, accessor):
        super().__init__()
        self._accessor = accessor
        self.employeeDataAccessObject = EmployeeDataAccessObject()

    def create(self, employee):
        if self._accessor == Accessor.ADMIN:
            self.employeeDataAccessObject.create(employee)
        else:
            raise PermissionError("Not authorised to create Employee.")

    def get(self, employee_id):
        if self._accessor == Accessor.ADMIN or self._accessor == Accessor.USER:
            return self.employeeDataAccessObject.get(employee_id)
        else:
            raise PermissionError("Not authorised to get Employee Data.")

    def delete(self, employee_id):
        if self._accessor == Accessor.ADMIN:
            self.employeeDataAccessObject.delete(employee_id)
        else:
            raise PermissionError("Not authorised to delete Employee.")

    def return_all_employees(self):
        if self._accessor == Accessor.ADMIN:
            return self.employeeDataAccessObject.return_all_employees()
        else:
            raise PermissionError("Not authorised to get data of all Employees.")


def main():
    employee_names = ['Arpan', 'Moin', 'Samay', 'Sambhav', 'Anmol', "Vinay"]
    employees = []
    for emp_id, employee_name in enumerate(employee_names, start=1000):
        employees.append(Employee(employee_name, emp_id))

    admin_data_access_proxy = EmployeeDataAccessProxy(Accessor.ADMIN)
    user_data_access_proxy = EmployeeDataAccessProxy(Accessor.USER)

    print(f"\nTrying to add employees to data access layer as {Accessor.USER.value}:")
    try:
        for employee in employees:
            user_data_access_proxy.create(employee)
    except PermissionError as e:
        print(f"Encountered Following Permission error: {e}")

    print(f"\nAdding employees to data access layer as {Accessor.ADMIN.value}:")
    for employee in employees:
        admin_data_access_proxy.create(employee)

    print(f"\nFetching data for all employees as {Accessor.ADMIN.value}:")
    print(admin_data_access_proxy.return_all_employees())

    print(f"\nFetching Arpan's data as {Accessor.USER.value}:")
    print(user_data_access_proxy.get(1000))

    print(f"\nFetching Arpan's data as {Accessor.ADMIN.value}:")
    print(admin_data_access_proxy.get(1000))

    print(f"\nTrying to Delete employee as {Accessor.USER.value}")
    try:
        print(user_data_access_proxy.delete(1000))
    except PermissionError as e:
        print(f"Encountered Following Permission error: {e}")

    print(f"\nDeleting Arpan as {Accessor.ADMIN.value}")
    print(admin_data_access_proxy.delete(1000))

    print(f"\nDeleting Invalid employee as {Accessor.ADMIN.value}")
    try:
        print(admin_data_access_proxy.delete(12345))
    except KeyError as e:
        print(f"Encountered the following Key error: {e}")

    print(f"\nFetching data for all employees as {Accessor.ADMIN.value} after deleting Arpan:")
    print(admin_data_access_proxy.return_all_employees())


if __name__ == '__main__':
    main()


"""
Expected Output:

Trying to add employees to data access layer as User:
Encountered Following Permission error: Not authorised to create Employee.

Adding employees to data access layer as Admin:
Created an employee: Employee ID: 1000, Employee Name: Arpan
Created an employee: Employee ID: 1001, Employee Name: Moin
Created an employee: Employee ID: 1002, Employee Name: Samay
Created an employee: Employee ID: 1003, Employee Name: Sambhav
Created an employee: Employee ID: 1004, Employee Name: Anmol
Created an employee: Employee ID: 1005, Employee Name: Vinay

Fetching data for all employees as Admin:
[Employee(Arpan, 1000), Employee(Moin, 1001), Employee(Samay, 1002), Employee(Sambhav, 1003), Employee(Anmol, 1004), Employee(Vinay, 1005)]

Fetching Arpan's data as User:
Fetched employee with Employee ID: 1000
Employee ID: 1000, Employee Name: Arpan

Fetching Arpan's data as Admin:
Fetched employee with Employee ID: 1000
Employee ID: 1000, Employee Name: Arpan

Trying to Delete employee as User
Encountered Following Permission error: Not authorised to delete Employee.

Deleting Arpan as Admin
Deleted employee with Employee ID: 1000
None

Deleting Invalid employee as Admin
Encountered the following Key error: 'No employee present with employee_id: 12345'

Fetching data for all employees as Admin after deleting Arpan:
[Employee(Moin, 1001), Employee(Samay, 1002), Employee(Sambhav, 1003), Employee(Anmol, 1004), Employee(Vinay, 1005)]

Process finished with exit code 0

"""
