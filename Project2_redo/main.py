import re

from course import Course, AVLTree, AVLNode

courses = AVLTree()

def load_courses():
    with open('courses.txt') as f:
        for line in f:
            line=line.strip()
            course_name,course_info = line.split(':',1)
            hours,course_code,department,topics = re.split('#|/',course_info)
            topics = topics.split(',')
            course = Course(course_code,course_name,department,topics,hours)
            courses.insert(course)
            
            
def insert_course():
    print('Insert a new course.')
    course_code = input('Enter course code: ')
    course_name = input('Enter course name: ')
    department = input('Enter department: ')
    topics = input('Enter topics: ')
    hours = input('Enter hours: ')
    course = Course(course_code,course_name,department,topics,hours)
    courses.insert(course)
    print('Course inserted.')
    
    
def find_and_update_course():
    print('Find and update a course.')
    course_code = input('Enter course code: ')
    course = courses.search(course_code)
    if course is None:
        print('Course not found.')
    else:
        print(course)
        print('Do you want to update this course? (Y/N)')
        choice = input('Enter your choice: ')
        if choice == 'Y':
            print('1. Update course code.')
            print('2. Update course name.')
            print('3. Update department.')
            print('4. Update topics.')
            print('5. Update hours.')
            print('0. Exit')
            choice = input('Enter your choice: ')
            if choice == '1':
                print('Update course code.')
                course_code = input('Enter course code: ')
                courses.delete(course.course_code)
                course.course_code = course_code
                courses.insert(course)
                print('Course code updated.')
            elif choice == '2':
                print('Update course name.')
                course_name = input('Enter course name: ')
                course.course_name = course_name
                print('Course name updated.')
            elif choice == '3':
                print('Update department.')
                department = input('Enter department: ')
                course.department = department
                print('Department updated.')
            elif choice == '4':
                print('Update topics.')
                topics = input('Enter topics: ')
                course.topics = topics
                print('Topics updated.')
            elif choice == '5':
                print('Update hours.')
                hours = input('Enter hours: ')
                course.hours = hours
                print('Hours updated.')
            elif choice == '0':
                pass
            else:
                print('Invalid choice.')
        elif choice == 'N':
            pass
        else:
            print('Invalid choice.')
            
def list_courses_in_lexicographic_order():
    print('List courses in lexicographic order.')
    courses.print_tree_in_order()
    
    
def list_all_courses_in_lexicographic_order_that_belong_to_the_same_department():
    print('List all courses in lexicographic order that belong to the same department.')
    department = input('Enter department: ')
    courses.list_all_courses_in_lexicographic_order_that_belong_to_the_same_department(department)
    
def list_all_topics_associated_with_a_given_course():
    print('List all topics associated with a given course.')
    course_code = input('Enter course code: ')
    course_node = courses.search(course_code)
    if course_node is None:
        print('Course not found.')
    else:
        print(course_node.course.topics)
        

def delete_a_course():
    print('Delete a course.')
    course_code = input('Enter course code: ')
    course = courses.search(course_code)
    if course is None:
        print('Course not found.')
    else:
        courses.delete(course_code)
        print('Course deleted.')
    
def delete_all_courses_that_start_with_a_specific_letter():
    print('Delete all courses that start with a specific letter.')
    letter = input('Enter a letter: ')
    courses.delete_all_courses_that_start_with_a_specific_letter(letter)
    print('All courses that start with a specific letter deleted.')
    
def delete_all_courses_belong_to_a_given_department():
    print('Delete all courses belong to a given department.')
    department = input('Enter department: ')
    courses.delete_all_courses_belong_to_a_given_department(department)
    print('All courses belong to a given department deleted.')

def save_data():
    print('Save Data.')
    courses.save_data()
    print('Data saved.')

def print_tree_in_tree_structure():
    print('Print the tree in tree structure.')
    courses.print_tree()

def menu():
    print('1. Read Information from file.')
    print('2. Insert new course.')
    print('3. Find or Update a course.')
    print('4. List courses in lexicographic order.')
    print('5. List all topics associated with a given course.')
    print('6. List all courses in lexicographic order that belong to the same department.')
    print('7. Delete a course.')
    print('8. Delete all courses that start with a specific letter.')
    print('9. Delete all courses belong to a given department.')
    print('10. Save Data.')
    print('11. Print the tree in tree structure')
    print('0. Exit')
    choice = input('Enter your choice: ')
    return choice   
            
def main():
    while True:
        choice = menu()
        if choice == '1':
            load_courses()
            courses.print_tree()
        elif choice == '2':
            insert_course()
        elif choice == '3':
            find_and_update_course()
        elif choice == '4':
            list_courses_in_lexicographic_order()
        elif choice == '5':
            list_all_topics_associated_with_a_given_course()
        elif choice == '6':
            list_all_courses_in_lexicographic_order_that_belong_to_the_same_department()
        elif choice == '7':
            delete_a_course()
        elif choice == '8':
            delete_all_courses_that_start_with_a_specific_letter()
        elif choice == '9':
            delete_all_courses_belong_to_a_given_department()
        elif choice == '10':
            save_data()
        elif choice == '11':
            print_tree_in_tree_structure()
        elif choice == '0':
            break
        else:
            print('Invalid input.')
    
if __name__ == '__main__':
    main()
            
            
            
            