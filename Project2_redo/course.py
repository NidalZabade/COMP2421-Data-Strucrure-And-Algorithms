
class Course:
    def __init__(self,course_code:str,course_name:str, department:str, topics:list, hours:int):
        self.course_code = course_code
        self.course_name = course_name
        self.department = department
        self.topics = topics
        self.hours = hours

    def __str__(self):
        return f"{self.course_code} {self.course_name} {self.department} {self.topics} {self.hours}"
    
    
class AVLNode:
    def __init__(self, course:Course):
        self.course = course
        self.left = None
        self.right = None
        self.height = 0

    def __str__(self):
        return f"{self.course}"


class AVLTree:
    def __init__(self):
        self.root = None

    def insert(self, course:Course):
        self.root = self._insert(course, self.root)

    def _insert(self, course:Course, node:AVLNode):
        if node is None:
            return AVLNode(course)
        if course.course_code < node.course.course_code:
            node.left = self._insert(course, node.left)
        else:
            node.right = self._insert(course, node.right)
        return self._balance(node)

    def _balance(self, node:AVLNode):
        if self._height(node.left) - self._height(node.right) > 1:
            if self._height(node.left.left) >= self._height(node.left.right):
                node = self._rotate_right(node)
            else:
                node = self._rotate_left_right(node)
        elif self._height(node.right) - self._height(node.left) > 1:
            if self._height(node.right.right) >= self._height(node.right.left):
                node = self._rotate_left(node)
            else:
                node = self._rotate_right_left(node)
        node.height = max(self._height(node.left), self._height(node.right)) + 1
        return node

    def _rotate_right(self, node:AVLNode):
        temp = node.left
        node.left = temp.right
        temp.right = node
        node.height = max(self._height(node.left), self._height(node.right)) + 1
        temp.height = max(self._height(temp.left), node.height) + 1
        return temp

    def _rotate_left(self, node:AVLNode):
        temp = node.right
        node.right = temp.left
        temp.left = node
        node.height = max(self._height(node.left), self._height(node.right)) + 1
        temp.height = max(self._height(temp.right), node.height) + 1
        return temp

    def _rotate_left_right(self, node:AVLNode):
        node.left = self._rotate_left(node.left)
        return self._rotate_right(node)

    def _rotate_right_left(self, node:AVLNode):
        node.right = self._rotate_right(node.right)
        return self._rotate_left(node)

    def _height(self, node:AVLNode):
        if node is None:
            return -1
        return node.height

    def __str__(self):
        return self._str(self.root)
    
    def _str(self, node:AVLNode):
        if node is None:
            return ""
        return f"{self._str(node.left)}{node}{self._str(node.right)}"

    def _print_tree(self, node:AVLNode, level:int):
        if node is None:
            return
        self._print_tree(node.right, level+1)
        print(' ' * 4 * level + '->', node.course.course_code)
        self._print_tree(node.left, level+1)
    
    def print_tree(self):
        self._print_tree(self.root, 0)
        
    
    def search(self, course_code:str):
        return self._search(course_code, self.root)
    
    def _search(self, course_code:str, node:AVLNode):
        if node is None:
            return None
        if course_code == node.course.course_code:
            return node
        elif course_code < node.course.course_code:
            return self._search(course_code, node.left)
        else:
            return self._search(course_code, node.right)

    def delete(self, course_code:str):
        self.root = self._delete(course_code, self.root)
        
    def _delete(self, course_code:str, node:AVLNode):
        if node is None:
            return None
        if course_code < node.course.course_code:
            node.left = self._delete(course_code, node.left)
        elif course_code > node.course.course_code:
            node.right = self._delete(course_code, node.right)
        else:
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            else:
                temp = self._find_min(node.right)
                node.course = temp.course
                node.right = self._delete(temp.course.course_code, node.right)
        return self._balance(node)
    
    def _print_tree_in_order(self, node:AVLNode):
        if node is None:
            return
        self._print_tree_in_order(node.left)
        print(node.course.course_code)
        self._print_tree_in_order(node.right)
        
    def print_tree_in_order(self):
        self._print_tree_in_order(self.root)
        
    def _find_min(self, node:AVLNode):
        if node.left is None:
            return node
        return self._find_min(node.left)
    
    def find_min(self):
        return self._find_min(self.root)
    
    def _find_max(self, node:AVLNode):
        if node.right is None:
            return node
        return self._find_max(node.right)
    
    def find_max(self):
        return self._find_max(self.root)
    
    def _print_tree_pre_order(self, node:AVLNode):
        if node is None:
            return
        print(node.course.course_code)
        self._print_tree_pre_order(node.left)
        self._print_tree_pre_order(node.right)
        
    def print_tree_pre_order(self):
        self._print_tree_pre_order(self.root)
        
    def _print_tree_post_order(self, node:AVLNode):
        if node is None:
            return
        self._print_tree_post_order(node.left)
        self._print_tree_post_order(node.right)
        print(node.course.course_code)
        
    def print_tree_post_order(self):
        self._print_tree_post_order(self.root)
        
    def delete_all_courses_that_start_with_a_specific_letter(self, letter:str):
        self.root = self._delete_all_courses_that_start_with_a_specific_letter(letter, self.root)
        
    def _delete_all_courses_that_start_with_a_specific_letter(self, letter:str, node:AVLNode):
        if node is None:
            return None
        node.left = self._delete_all_courses_that_start_with_a_specific_letter(letter, node.left)
        node.right = self._delete_all_courses_that_start_with_a_specific_letter(letter, node.right)
        if node.course.course_code[0] == letter:
            return self._delete(node.course.course_code, node)
        return node
    
    def delete_all_courses_that_start_with_a_specific_letter(self, letter:str):
        self.root = self._delete_all_courses_that_start_with_a_specific_letter(letter, self.root)
        
    def _delete_all_courses_that_start_with_a_specific_letter(self, letter:str, node:AVLNode):
        if node is None:
            return None
        node.left = self._delete_all_courses_that_start_with_a_specific_letter(letter, node.left)
        node.right = self._delete_all_courses_that_start_with_a_specific_letter(letter, node.right)
        if node.course.course_code[0] == letter:
            return self._delete(node.course.course_code, node)
        return node
    
    def _list_all_courses_in_lexicographic_order_that_belong_to_the_same_department(self, department:str, node:AVLNode):
        if node is None:
            return
        self._list_all_courses_in_lexicographic_order_that_belong_to_the_same_department(department, node.left)
        if node.course.department == department:
            print(node.course.course_code)
        self._list_all_courses_in_lexicographic_order_that_belong_to_the_same_department(department, node.right)
    
    
    def list_all_courses_in_lexicographic_order_that_belong_to_the_same_department(self, department:str):
        self._list_all_courses_in_lexicographic_order_that_belong_to_the_same_department(department, self.root)
        
    def delete_all_courses_belong_to_a_given_department(self, department:str):
        self.root = self._delete_all_courses_belong_to_a_given_department(department, self.root)
    
    def _delete_all_courses_belong_to_a_given_department(self, department:str, node:AVLNode):
        if node is None:
            return None
        node.left = self._delete_all_courses_belong_to_a_given_department(department, node.left)
        node.right = self._delete_all_courses_belong_to_a_given_department(department, node.right)
        if node.course.department == department:
            return self._delete(node.course.course_code, node)
        return node
    
    def save_data(self):
        self._print_courses_in_file(self.root)

        
    def _print_courses_in_file(self, node:AVLNode):
        with open("offered_courses.txt", "w") as f:
            if node is None:
                return
            self._print_courses_in_file(node.left)
            f.write(node.course.course_name + ":" + str(node.course.hours) + "#" + node.course.course_code + "#" + node.course.department + "/" + ",".join(node.course.topics))
            self._print_courses_in_file(node.right)
    