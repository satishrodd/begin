import pickle
import os

def get_abs_path(filename):
    dir = os.path.dirname(__file__)
    return os.path.join(dir, filename) 

class person:
    id =  0
    firstname = ""
    lastname = ""
		
    #will be called when instancized
    def __init__(self, idi, fn, ln):
    	self.id = idi
	self.firstname = fn
	self.lastname = ln
    def print_self(self):
	print(self.id, self.firstname, self.lastname)
		
    def persistent_id(self):
        if hasattr(self, 'id'):
            return 'the value %d' % self.id
        else:
            return None
    def persistent_load(persid):
        if persid.startswith('the value '):
            value = int(persid.split()[1])
            return person(value)
        else:
            raise pickle.UnpicklingError, 'Invalid persistent id'
		

#instantiate the class
bob = person(2, "sat", "rodd")
sat = person(3, "hello", "world")

# You need to use 2 file pointers, one each for reading(loading) and writing(dumping).
file_name = get_abs_path('abc.txt') 
file = open(file_name, "r+b")
file1 = open(file_name, "rb")

#write the object to the file.
#pickle.dump(bob, file)
push= pickle.Pickler(file)
push.persistent_id = person.persistent_id
push.persistent_load = person.persistent_load
pull = pickle.Unpickler(file1)
pull.persistent_id = person.persistent_id
pull.persistent_load = person.persistent_load

push.dump(bob)
push.dump(sat)

try:
	# read the object from file
	x = pull.load()
	x.print_self()
except EOFError:
	print("EOF error")
#except :
#	print("exception")
