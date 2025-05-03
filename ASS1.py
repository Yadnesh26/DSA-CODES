def initializeHashTable():
    size = int(input('Enter size of hash table: '))
    hashtable = [[-1, 'null'] for _ in range(size)]
    print(f'Hashtable of size {size} is successfully created.')
    return size, hashtable

def linearProbing(size, hashtable):
    count = 0
    while True:
        print('\nMenu for Linear Probing')
        print('1. Insert')
        print('2. Search')
        print('3. Display')
        print('4. Back')
        choice = int(input('Enter your choice: '))

        if choice == 1:
            if count == size:
                print('Hash table is Full.')
                continue

            number = int(input('Enter number: '))
            name = input('Enter Name: ')
            hashvalue = number % size
            original_hash = hashvalue

            while hashtable[hashvalue][0] != -1:
                print('Collision occurred. Using Linear Probing...')
                hashvalue = (hashvalue + 1) % size
                if hashvalue == original_hash:
                    print('Table is full. Insertion failed.')
                    break
            else:
                hashtable[hashvalue] = [number, name]
                count += 1
                print(f'Data inserted at index {hashvalue}. Total records: {count}')

        elif choice == 2:
            number = int(input('Enter number to search: '))
            hashvalue = number % size
            comparisons = 0

            while hashtable[hashvalue][0] != number and comparisons < size:
                hashvalue = (hashvalue + 1) % size
                comparisons += 1

            if hashtable[hashvalue][0] == number:
                print(f'Number {number} found at index {hashvalue} with {comparisons + 1} comparisons.')
            else:
                print(f'Number NOT found. Comparisons: {comparisons + 1}')

        elif choice == 3:
            print('\nHash Table:')
            for i in range(size):
                print(f'Index {i}: {hashtable[i]}')

        elif choice == 4:
            break

        else:
            print('Invalid choice.')

def doubleHashing(size, hashtable):
    prime = int(input('Enter a prime number less than size for Double Hashing: '))
    count = 0

    while True:
        print('\nMenu for Double Hashing')
        print('1. Insert')
        print('2. Search')
        print('3. Display')
        print('4. Back')
        choice = int(input('Enter your choice: '))

        if choice == 1:
            if count == size:
                print('Hash table is Full.')
                continue

            number = int(input('Enter number: '))
            name = input('Enter Name: ')
            hash1 = number % size
            hash2 = prime - (number % prime)
            i = 0

            while i < size:
                new_hash = (hash1 + i * hash2) % size
                if hashtable[new_hash][0] == -1:
                    hashtable[new_hash] = [number, name]
                    count += 1
                    print(f'Data inserted at index {new_hash}. Total records: {count}')
                    break
                else:
                    print('Collision occurred. Using Double Hashing...')
                i += 1
            else:
                print('Table is full or insertion failed.')

        elif choice == 2:
            number = int(input('Enter number to search: '))
            hash1 = number % size
            hash2 = prime - (number % prime)
            i = 0
            comparisons = 0

            while i < size:
                new_hash = (hash1 + i * hash2) % size
                comparisons += 1
                if hashtable[new_hash][0] == number:
                    print(f'Number {number} found at index {new_hash} with {comparisons} comparisons.')
                    break
                elif hashtable[new_hash][0] == -1:
                    print(f'Number NOT found. Comparisons: {comparisons}')
                    break
                i += 1
            else:
                print(f'Number NOT found. Comparisons: {comparisons}')

        elif choice == 3:
            print('\nHash Table:')
            for i in range(size):
                print(f'Index {i}: {hashtable[i]}')

        elif choice == 4:
            break

        else:
            print('Invalid choice.')

# Main Program
choice = 0
while choice != 3:
    print('\n\nMain Menu')
    print('1. Linear Probing')
    print('2. Double Hashing')
    print('3. Exit')
    choice = int(input('Enter your choice: '))

    if choice == 1:
        size, hashtable = initializeHashTable()
        linearProbing(size, hashtable)

    elif choice == 2:
        size, hashtable = initializeHashTable()
        doubleHashing(size, hashtable)

    elif choice == 3:
        print('Program exited.')

    else:
        print('Invalid choice. Please try again.')

