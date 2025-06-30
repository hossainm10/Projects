
def add(n1,n2):
    return n1 + n2
def mult(n1,n2):
    return n1 * n2
def sub(n1,n2):
    return n1-n2
def div(n1,n2):
    return n1/n2

operations = {
    "+": add,
    "-": sub,
    "*": mult,
    "/": div,

}

print("Welcome to calculator game!")





def calculator():
    
    num1=float(input("Enter the first number: "))
    while True:
        num2=float(input("Enter the second number: "))
        chosen_oper=input("Which operation would you like to complete? \n")
        for symbol in operations:
            print(symbol)

        
        if chosen_oper in ['+','*','-',"/"]:
            
            print(f'You have selected {chosen_oper}. We will perform {num1} {chosen_oper} {num2}! ')
            result=operations[chosen_oper](num1,num2)
        else:
            print("Please enter a valid operation like *,+,-,/ ")
            continue
        
        print(f"You computed {num1} {chosen_oper} {num2} and the result is {result}")
        decision=input(f"Would you like to perform a new operation on {result}(type'y') or not(new result, type 'n')? ").lower()
        if decision =="y":
            num1=result
        else:
            exit= input("Would you like to terminate this program? Type y for yes or n for no: ")
            if exit =='y':
                break
            else:
                calculator()


calculator()
print("Program terminated. Thank you for using my calculator!")