class Nod:
    def __init__(self, e):
        self.e = e
        self.urm = None
    
class Lista:
    def __init__(self):
        self.prim = None
        

'''
crearea unei liste din valori citite pana la 0
'''
def creareLista():
    lista = Lista()
    lista.prim = creareLista_rec()
    return lista

def creareLista_rec():
    x = int(input("x="))
    if x == 0:
        return None
    else:
        nod = Nod(x)
        nod.urm = creareLista_rec()
        return nod
    
'''
tiparirea elementelor unei liste
'''
def tipar(lista):
    tipar_rec(lista.prim)
    
def tipar_rec(nod):
    if nod != None:
        print (nod.e)
        tipar_rec(nod.urm)
        
'''
add function at the end of the list
'''

def addEnd(lista, x):
    lista.prim = addEnd_rec(lista.prim, x)

def addEnd_rec(nod, x):
    if nod == None:
        return Nod(x)
    else:
        nod.urm = addEnd_rec(nod.urm,x)
        return nod

'''
concatenate 2lists
'''

def concat(lista1, lista2):
    lista1.prim = concat_rec(lista1.prim, lista2.prim)
    return lista1

def concat_rec(nod1, nod2):
    if nod1 == None:
        return nod2
    else:
        nod1.urm = concat_rec(nod1.urm, nod2)
        return nod1


    

'''
program pentru test
'''


        
def main():
    list = creareLista()
    list2 = creareLista()
    addEnd(list, 5)
    tipar(concat(list, list2))
    
main() 
    
    
    
    
    