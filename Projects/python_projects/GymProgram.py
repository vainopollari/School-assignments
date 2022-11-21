class Day:
    def __init__(self, name):
        self.name = name
        self.list = []

    def printDay(self):
        for exercise in self.list:
            print(exercise)



class Exercise:
    def __init__(self, name, reps, day):
        self.name = name
        self.reps = reps



#Main program for testing classes
def main():
    START_STRING = "Start by entering workout day name to program (for example push, pull, legs etc.): "
    COMMAND_STRING = "Enter 1 if you want to add new workout day to your program or 2 if you want to enter new exercise: "
    NEW_DAY_NAME = "Enter workout day name (for example push, pull, legs etc.): "
    NEW_EXERCISE = "Enter exercise name: "
    REPS_STRING = "Enter reps for the exercise: "

    Dayname = input(START_STRING)
    workout = Day(Dayname)
    while command != 1 or command != 2:
        command = input(COMMAND_STRING)
        if command != 1 or command != 2:
            print("Enter 1 or 2")
    
    if command == 1:
        Dayname = input(NEW_DAY_NAME)
        workout = Day(Dayname)

    elif command == 2:
        exer_name = input(NEW_EXERCISE)
        exer_reps = input(REPS_STRING)






if __name__ == "__main__":
    main()