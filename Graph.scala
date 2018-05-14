import scala.collection.mutable.HashMap
import scala.collection.mutable.HashSet
import scala.collection.mutable.ListBuffer
import scala.collection.immutable.List
import util.control.Breaks._
object Graph extends App{
    //Visible to all instances including subclasses
    //private val nodeLookUp:HashMap = HashMap[Int, Node] ()
    // Visible to one instance of  class but including subclasses
    // Use new method if override is used. Apply only works with default setting on companion object
    private[this] val nodeLookUp: HashMap[Int, Node] = new HashMap[Int, Node] (){ override def default(key:Int) = Node(-1,ListBuffer[Node]()) }
    private[this] case class Node(val id:Int, val adjacent:ListBuffer[Node]){}
    private[this] def getNode(id: Int):Node = {
        nodeLookUp(id)
    }
    def addNodes(nodes: List[Int]):Unit = 
        for(node <- nodes) {
            nodeLookUp+=(node->Node(node,ListBuffer[Node]()))
        }
    
    def addEdge(source: Int, destination: Int):Unit = {
        val s:Node = getNode(source)
        val d:Node = getNode(destination)
        s.adjacent+=d
    }
    def hasPathDFS(source:Int, destination: Int):Boolean ={
        val s = getNode(source)
        val d = getNode(destination)
        val visited = HashSet[Int]()
        hasPathDFS(s,d, visited)
    }
    def hasPathBFS(source:Int, destination: Int):Boolean ={
        val s = getNode(source)
        val d = getNode(destination)
        hasPathBFS(s,d)
    }
    private[this] def hasPathBFS(source:Node, destination:Node):Boolean = {
        val nextToVisit = ListBuffer[Node]()
        val visited = HashSet[Int]()
        nextToVisit+=source
        while(!nextToVisit.isEmpty){
            val node = nextToVisit.remove(0)
            if(node == destination)
                return true
            breakable {
                if(visited.contains(node.id))
                    break
                visited+=node.id
                for(child <- node.adjacent)
                    nextToVisit+=child
            }
        }
        return false
    }
    private[this] def hasPathDFS(source:Node, destination:Node,
        visited:HashSet[Int]):Boolean = {
        if(visited.contains(source.id))
            return false
        else{
            visited.add(source.id)
            if(source == destination)
                return true
            for(child <- source.adjacent ){
                if(hasPathDFS(child, destination, visited))
                    return true
            }
        }
        return false
    }
    val vertices = List(0,1,2,3,4,5,6)
    addNodes(vertices)
    addEdge(0,1)
    addEdge(0,2)
    addEdge(1,3)
    addEdge(2,4)
    addEdge(3,5)
    println(nodeLookUp.size)
    println(nodeLookUp)
    println(hasPathDFS(0,6))
    println(hasPathBFS(0,6))
}