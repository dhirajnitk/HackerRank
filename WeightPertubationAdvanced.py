##################################################################
####For any queries with the code contact Dhiraj <dhirajnitk@gmail.com>
#################################################################
from collections import defaultdict
from pprint import pprint
from functools import reduce
import csv
import random
import sys
import matplotlib.pyplot as plt
#Max Value needed in  Floyd Warshall Shortest Distance
INF  = 100000
edges = set()
#Sampling Number from [1,RandomMax] for increasing non visited edge length
RandomMax = 100
#Local decrease/increase perturbation via iterative method gives fast convergence  as compared to global method mentioned in Xi's reserach paper.
# True for Global and False for Local
GlobalGreedy = True

#Fixing Seed to repeat same behavior across many run of program. You can comment it to get variable results for every run of code
#Comment this line to get different H combinations leading to different plots

#random.seed(1819)
#File reading from Csv. It can stand many new lines at end of file
weights = list(csv.reader(open("Weights.csv")))
# Removes trailing new line with filter high order function
weights  = list(filter(None, weights))
V = len(weights)
#Check for Matrix input to  be square
if(V != len(weights[0])):
    print("Weight Matrix input must be square")
    sys.exit()

#Convert 2 d weight matrix of char to int with higher order lamda, map function. 
weights = list(map(lambda i : list(map(lambda j :int(j) , i)) , weights))
# Forces weights[i][i] to  0.
weights = [ [ 0  if i == j  else weights[i][j] for i in range(V) ] for j in range(V)]
#HMaxLen is superset of HLen and it lies between [3,V)
HMaxLen = random.randint(3, V)
#H : In Social media; business and privacy criteria decides which nodes to be kept private and which ones to be left public.
#Aim is to be persistent with valuable information and keep them as public but shake the private information to the limit that doesn't affect behavior of public information.
#Since we don't know the origin, use-case of our graph. We Generate H randomly with replacement from shuffle function.
# Tuple are stored in set. They cant have duplicate entry. Source,Destination in a tuple cant be same node(as per use case of H)
def generateH():
    #HLen should be between [3, HMaxLen)
    HLen = random.randint(3, HMaxLen)
    H = set()
    VAll= list(range(V))
    for i in range(HLen):
        random.shuffle(VAll)
        newNode = (VAll[0],VAll[1])
        H.add(newNode)
    return list(H)
H = generateH()
pprint("Randomly Generated H")
print(H)
#Calculate Edges from Adjacency matrix 
for i, v in enumerate(weights, 0):
    for j, u in enumerate(v, 0):
        if u != 0 and  u!= INF and frozenset([i, j]) not in edges and i !=j :
            edges.add(frozenset([i, j]))
print("Edges")
print(edges)
class GreedyWeightsPerturbation:
    #class variables shared by all instances
    # H = (1,6), (4,6), (3,6)
    #H be the set of targeted pairs whose shortest paths and the corresponding
    #path lengths should be preserved as much as possible.
    # d is shortest distance for entire weight matrix
    
    #create shortest path edges list from predecessor matrix
    def findShortestPath(self, nodes,pred):
        (source, destination) = nodes
        p = [destination]
        while source!= destination:
            #Python list is single linked. Time complexity is O(n) for single insertion at front. Use Deque instead for o(1)
            p.insert(0,pred[source][destination])
            destination = pred[source][destination]
        return p
    #Find shortest path distance matrix and predecessor matrix
    def FloydWarshallShortestDistance(self,w):
        w = list(map(lambda i : list(map(lambda j : j , i)) , w))
        pred = [ [i  for j in range(V)] for i in range(V) ]
        for k in range(V):
            for i in range(V):
                for j in range(V):
                    if(w[i][k] + w[k][j] < w[i][j]):
                        w[i][j] = w[i][k] + w[k][j]
                        pred[i][j] = k
        return (w,  pred)
    #Perturbation for Non Visited Edges
    def updateNonVisitedEdges(self,NonVisitedEdges,w):
        for (from_, to_) in NonVisitedEdges:
            w[from_][to_]+= random.randint(1, RandomMax)
            #Undirected graphs
            w[to_][from_] = w[from_][to_]
        (d, pred) = self.FloydWarshallShortestDistance(w)
        return (d, pred)
    #Perturbation for All Visited Edges
    def updateAllVisitedEdges(self,AllVisitedEdges,w):
        #No need to change predecessor
        for (from_, to_) in AllVisitedEdges:
            #random positive number which is smaller than wi,j. Hence(1,w)
            w[from_][to_]-= random.randint(1, w[from_][to_])
            #Undirected graphs
            w[to_][from_] = w[from_][to_]
        (d, pred) = self.FloydWarshallShortestDistance(w)
        return (d, pred)
    #Increase edges weight  for partial Visited Edges
    def increasePartialEdges(self, PathSets, partialEdge,d,w):
        w = list(map(lambda i : list(map(lambda j : j , i)) , w))
        (from_,to_) = partialEdge
        w[from_][to_] = INF
        w[to_][from_] = w[from_][to_]
        (d_, pred_) = self.FloydWarshallShortestDistance(w)
        t = INF
        for index, pathset in list(enumerate(PathSets)):
            if(partialEdge in pathset):
                (row, col) = H[index]
                t = min(d_[row][col]-d[row][col],t)
        return t-1
    #Decrease edges weight  for partial Visited Edges
    def decreasePartialEdges(self, PathSets, partialEdge,d,w):
        (from_,to_) = partialEdge
        t = INF
        for index, pathset in list(enumerate(PathSets)):
            if(partialEdge not in pathset):
                (row, col) = H[index]
                t = min(d[row][from_] +w[from_][to_]+d[to_][col]-d[row][col],t)             
        return t-1
    #Test if perturbation is increase for partial edges wrt initial global D. See Line no 7 in  algorithm. 
    def testPerturbation(self,partialEdge, d,w_):
        w_ = list(map(lambda i : list(map(lambda j : j , i)) , w_))
        (from_,to_) = partialEdge
        w_[from_][to_]= INF
        #Undirected graphs
        w_[to_][from_] = w_[from_][to_]
        (d_, pred_) = self.FloydWarshallShortestDistance(w_)
        count = 0
        for (from_, to_) in H:
            if d_[from_][to_] <  d[from_][to_]:
               count +=1
            else:
               count -=1
        if(count >0):
            return (True)
        else:
            return (False)
    def __init__(self, name):
        self.name = name    # instance variable unique to each instance
if __name__ == "__main__":
     w   = list(map(lambda i : list(map(lambda j : j , i)) , weights))
     #pprint("Initial Weight Matrix")
     #pprint(w)
     greedyGraph = GreedyWeightsPerturbation("Greedy")
     d,pred = greedyGraph.FloydWarshallShortestDistance(w)
     print("Shortest Distance Adjacency Matrix")
     print(d)
     print("");
     print("Pure Predecessor Adjacency Matrix")
     print(pred)
     print("");
     PathSets = []
     for node in H:
         p = greedyGraph.findShortestPath(node,pred)
         PathSets.append(set([frozenset([x,y]) for x, y in zip(p[:-1], p[1:])]))
     print("Shortest Path Sets")
     print(PathSets)
     UnionEdges = set.union(*PathSets)
     print("All Visited Edges")
     #As number of public edges in H increase, the probability of finding  unique intersection in all sets of shortest paths reduces exponentially with size P( 1 in million cases for P of size 7/8)
     AllVisitedEdges = set.intersection(*PathSets)
     print(AllVisitedEdges)
     print("");
     print("Non Visited edges")
     NonVisitedEdges = edges- set.union(*PathSets)
     print(NonVisitedEdges)
     print("");
     print("Partial Visited edges")
     #Remove All visited edges from Union
     PartialEdgesSet = UnionEdges - AllVisitedEdges
     print(PartialEdgesSet)
     print("");
     #print("Partial Visited edges in order of Decreasing Frequency")
     CountSets = reduce(list.__add__,list(map(lambda x: list(x), list(PathSets))))
     EdgeFreq = {i:CountSets.count(i) for i in PartialEdgesSet}
     print("Sorted Partial Visited edges by Decreasing Frequency")
     SortedEdgeFreq= dict(sorted(EdgeFreq.items(), key=lambda item: item[1],reverse = True))
     print(SortedEdgeFreq)
     #Persistent w_ across all three perturbation
     w_   = list(map(lambda i : list(map(lambda j : j , i)) , w))
     print("Update Non Visited Edges")
     #Automatically updates w_ 
     (d_, pred_)=greedyGraph.updateNonVisitedEdges(NonVisitedEdges,w_)
     print(d_)
     print("Update All Visited Edges")
     (d_, pred_)=greedyGraph.updateAllVisitedEdges(AllVisitedEdges,w_)
     # D* is  automatically updated after every steps of perturbation
     

     print("Popping partially visited edges one by one in decreasing order of frequency")
     print("Appying Proposition 9 or Preposition 10")
     
     #print("Distance Matrix Before Final pertubation")
     #pprint(d_)
     for edge in  SortedEdgeFreq:
         #pprint(edge)
         #Global Perturbation  is w.r.t  d from beginning. it decides if graph at given edge needs to be increased/decreased
         increaseFlag = greedyGraph.testPerturbation(edge, d,w_)
         (from_,to_) = edge
         #Keep updating w_ iteratively in greedy manner
         if(increaseFlag):
                 #Local increase perturbation via iterative method gives fast convergence  as compared to global one mentioned in Xi reserach paper
                 # Add this to your report. Its different from Xi solution
                 #Local
                 if(not GlobalGreedy):
                     t= greedyGraph.increasePartialEdges(PathSets, edge,d_,w_)
                 #Global
                 else:
                     t= greedyGraph.increasePartialEdges(PathSets, edge,d,w_)
                 if(not t or t <= -1):
                     print("No Increase Perturbation possible For above case")
                     continue
                 w_[from_][to_]+= t
                 w_[to_][from_] = w_[from_][to_]
                 d_old,pred_new = greedyGraph.FloydWarshallShortestDistance(w_)
                 #Checking weight perturbation doesnt cause shortest path for all H to change
                 #If it does then we roll back to old weights and dont perturb for the given edge.
                 for node in H:
                     p = greedyGraph.findShortestPath(node,pred_)
                     p_new = greedyGraph.findShortestPath(node,pred_new)
                     if(not set([frozenset([x,y]) for x, y in zip(p[:-1], p[1:])])) == set([frozenset([x,y]) for x, y in zip(p_new[:-1], p_new[1:])]) :
                         w_[from_][to_]-= t
                         w_[to_][from_] = w_[from_][to_]
                         print("No increase Perturbation possible if shortest path is changed")
                         break
                 d_ = d_old
                 print("Increase Perturbation of {}".format(t))
                 
         else:
                 #Local decrease perturbation via iterative method gives fast convergence as compared to global one mentioned in Xi reserach paper
                 # Add this to your report. Its different from Xi solution
                 #Local
                 if(not GlobalGreedy):
                     u= greedyGraph.increasePartialEdges(PathSets, edge,d_,w_)
                 #Global
                 else:
                     u= greedyGraph.increasePartialEdges(PathSets, edge,d,w_)
                 if(not u or u <= -1 or w_[from_][to_] == 1):
                     print("No Decrease Perturbation possible For above case")
                     continue
                 if(w_[from_][to_] < u):
                     temp = w_[from_][to_]
                     #No such case mentioned in Research Paper
                     #Heuristics demand weights to be reduced to  1 if u(calculated reduction value) is larger than w
                     w_[from_][to_]= 1
                     w_[to_][from_] = w_[from_][to_]
                     d_old,pred_new = greedyGraph.FloydWarshallShortestDistance(w_)
                     #Checking weight perturbation doesnt cause shortest path for all H to change
                     #If it does then we roll back to old weights and dont perturb for the given edge.
                     for node in H:
                         p = greedyGraph.findShortestPath(node,pred_)
                         p_new = greedyGraph.findShortestPath(node,pred_new)
                         if(not set([frozenset([x,y]) for x, y in zip(p[:-1], p[1:])])) == set([frozenset([x,y]) for x, y in zip(p_new[:-1], p_new[1:])]) :
                             w_[from_][to_] = temp
                             w_[to_][from_] = w_[from_][to_]
                             print("No Decrease Perturbation possible if shortest path is changed")
                             break
                     d_ = d_old
                     print("Decrease Perturbation of {}".format(temp-1))
                 else:
                     temp = w_[from_][to_]
                     w_[from_][to_]-= u
                     w_[to_][from_] = w_[from_][to_]
                     d_old,pred_new = greedyGraph.FloydWarshallShortestDistance(w_)
                     for node in H:
                         p = greedyGraph.findShortestPath(node,pred_)
                         p_new = greedyGraph.findShortestPath(node,pred_new)
                         if(not set([frozenset([x,y]) for x, y in zip(p[:-1], p[1:])])) == set([frozenset([x,y]) for x, y in zip(p_new[:-1], p_new[1:])]) :
                             w_[from_][to_] = temp
                             w_[to_][from_] = w_[from_][to_]
                             break
                     d_ = d_old
                     print("Decrease Perturbation of {}".format(u))
     w_final   = list(map(lambda i : list(map(lambda j : j , i)) , w_))
     d_final, pred_final = greedyGraph.FloydWarshallShortestDistance(w_final)
     #print("Distance Matrix After Final perturbation")
     #pprint(d_final)
     #print("Pred  Matrix Before Final perturbation")
     #pprint(pred)
     #print("Pred  Matrix After  Final perturbation")
     #pprint(pred_final)
     print("Testing: #Checking weight perturbation doesnt cause shortest path's(P) for all H to change")
     flag = True
     for node in H:
         p = greedyGraph.findShortestPath(node,pred)
         p_new = greedyGraph.findShortestPath(node,pred_final)
         if(not set([frozenset([x,y]) for x, y in zip(p[:-1], p[1:])])) == set([frozenset([x,y]) for x, y in zip(p_new[:-1], p_new[1:])]) :
             flag = false
             break
     # True implies no change and algorithm ran successfully
     print(flag)
     D_ = []
     D = []
     X = range(0,len(H))
     for row,col in H:
         D.append(d[row][col])
         D_.append(d_final[row][col])
     #X axis are Edges from H    
     plt.xlabel('Points')
     #Y axis are corresponding shortest min distance for d and d*    
     plt.ylabel('Shortest Distance')
     plt.title('D vs  Greedy Perturbed D*')
     plt.plot(X, D, 'r--', label="D")
     plt.plot(X, D_, 'b--', label="Greedy Perturbed D*")
     plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc=2,
           ncol=2, mode="expand", borderaxespad=0.)
     plt.show()          
               
     
     
