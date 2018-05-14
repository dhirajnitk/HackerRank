from collections import deque
class Graph:
    def __init__(self):
        self.__nodeLookUp={}
    class Node:
        def __init__(self,id,adjacent):
            self.__id = id
            self.__adjacent = adjacent
        @property
        def id(self):
            return self.__id
        @property
        def adjacent(self):
            return self.__adjacent
    def addNodes(self,nodes):
        for key in nodes:
            node = self.Node(key,[])
            self.__nodeLookUp[key] = node
    def __getNode(self,id):
        return self.__nodeLookUp[id]
    def addEdge(self,source,destination):
        s = self.__getNode(source)
        d = self.__getNode(destination)
        s.adjacent.append(d)
    def hasPathBFS(self,source, destination):
        s = self.__getNode(source)
        d = self.__getNode(destination)
        return self.__hasPathBFSVisit(s,d)
    def hasPathDFS(self,source, destination):
        s = self.__getNode(source)
        d = self.__getNode(destination)
        visited = set()
        return self.__hasPathDFSVisit(s,d,visited)
    def __hasPathBFSVisit(self,source, destination):
        visited = set()
        l = deque()
        l.append(source)
        while(l):
            node = l.popleft()
            if(node == destination):
                return True
            else:
                if(node.id in visited):
                    continue
                visited.add(node.id)
                for child in node.adjacent:
                    l.append(child)
        return False
    def __hasPathDFSVisit(self,source, destination, visited):
        if(source.id in visited):
            return False
        else:
            visited.add(source.id)
            if(source == destination):
                return True
            for child in source.adjacent:
                if(self.__hasPathDFSVisit(child,destination, visited)):
                    return True
        return False

if __name__ == '__main__':
    g = Graph()
    vertices = [0,1,2,3,4,5,6]
    g.addNodes(vertices)
    g.addEdge(0,1)
    g.addEdge(0,2)
    g.addEdge(1,3)
    g.addEdge(2,4)
    g.addEdge(3,5)
    print(g.hasPathDFS(1,5))
    print(g.hasPathBFS(0,1))
