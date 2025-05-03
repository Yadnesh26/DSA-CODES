class Set: 
    def __init__(self, elements=None): 
        self._elements = [] 
        if elements: 
            for element in elements: 
                self.add(element) 
 
    def add(self, element): 
        if element not in self._elements: 
            self._elements.append(element) 
 
    def remove(self, element): 
        if element in self._elements: 
            self._elements.remove(element) 
 
    def contains(self, element): 
        return element in self._elements 
 
    def size(self): 
        return len(self._elements) 
 
    def iterator(self): 
        return iter(self._elements) 
 
    def intersection(self, other_set): 
        common_elements = [e for e in self._elements if e in other_set._elements] 
        return Set(common_elements) 
 
    def union(self, other_set): 
        new_set = Set(self._elements) 
        for element in other_set._elements: 
            new_set.add(element) 
        return new_set 
 
    def difference(self, other_set): 
        unique_elements = [e for e in self._elements if e not in other_set._elements] 
        return Set(unique_elements) 
 
    def is_subset(self, other_set): 
        return all(e in other_set._elements for e in self._elements) 
 
    def __str__(self): 
        return "{ " + ", ".join(str(e) for e in self._elements) + " }" 
 
if __name__ == "__main__": 
    setA = Set([1, 2, 3, 4]) 
    setB = Set([3, 4, 5, 6]) 
 
    print("Set A:", setA) 
    print("Set B:", setB) 
 
    setA.add(5) 
    print("After adding 5 to Set A:", setA) 
 
    setB.remove(6) 
    print("After removing 6 from Set B:", setB) 
 
    print("Does Set A contain 3?", setA.contains(3)) 
    print("Size of Set B:", setB.size()) 
print("Intersection of Set A and Set B:", setA.intersection(setB)) 
print("Union of Set A and Set B:", setA.union(setB)) 
print("Difference between Set A and Set B:", setA.difference(setB)) 
print("Is Set A a subset of Set B?", setA.is_subset(setB))