from collections import defaultdict
from queue import PriorityQueue
from math import inf

class Node:

    def __init__(self, tag = None, h = None):
        self.tag = tag
        self.h = h

    def __lt__(self, other):
        return self.h < other.h

    def __repr__(self):
        return f"({ self.tag }, h = { self.h })"


class Edge_list:

    def __init__(self):
        self.neighbours = defaultdict(dict)

    def push(self, source, destination, weight):    #this will make sure references to ALL nodes are somewhere inside the list
        self.neighbours[source.tag][destination.tag] = { "node": destination, "weight": weight }
        self.neighbours[destination.tag][source.tag] = { "node": source, "weight": weight }

    def get_neighbours_list(self, source_tag):
        return list(self.neighbours[source_tag].values())

    def get_neighbours_dict(self, source_tag):
        return self.neighbours[source_tag]

    def get_weight(self, source_tag, destination_tag):
        return self.neighbours[source_tag][destination_tag]["weight"]



def reconstruct_path(came_from, current_tag, gscore, fscore):
    path = [f"(node = {current_tag}, f = {fscore[current_tag]}, g = {gscore[current_tag]})"]

    while current_tag in came_from:
        current_tag = came_from[current_tag]
        path.append(f"(node = {current_tag}, f = {fscore[current_tag]}, g = {gscore[current_tag]})")

    return reversed(path)



def astar(edges, start, end):
    open_set = PriorityQueue()
    open_set.put((0, start))    #use fscore as priority

    came_from = {}  #will store tags

    gscore = defaultdict(lambda: inf)
    gscore[start.tag] = 0

    fscore = defaultdict(lambda: inf)
    fscore[start.tag] = start.h

    while not open_set.empty():
        current = open_set.get()[1]
        if current == end:
            return reconstruct_path(came_from, current.tag, gscore, fscore)

        current_neighbours = edges.get_neighbours_list(current.tag)
        for neighbour in current_neighbours:
            tentative_gscore = gscore[current.tag] + edges.get_weight(current.tag, neighbour["node"].tag)

            if tentative_gscore < gscore[neighbour["node"].tag]:
                came_from[neighbour["node"].tag] = current.tag
                gscore[neighbour["node"].tag] = tentative_gscore
                fscore[neighbour["node"].tag] = gscore[neighbour["node"].tag] + neighbour["node"].h

                if neighbour["node"] not in [elem[1] for elem in list(open_set.queue)]:
                    open_set.put((fscore[neighbour["node"].tag], neighbour["node"]))

    return None




if __name__ == "__main__":
    nodes = {
        'a': Node('a', inf),
        'b': Node('b', 10),
        'c': Node('c', 3),
        'd': Node('d', 7),
        'e': Node('e', 8),
        'f': Node('f', 0),
        'g': Node('g', 14),
        'i': Node('i', 3),
        'j': Node('j', 1),
        'k': Node('k', 2)
    }

    edges = Edge_list()
    edges.push(nodes['a'], nodes['b'], 3)
    edges.push(nodes['a'], nodes['c'], 9)
    edges.push(nodes['a'], nodes['d'], 7)
    edges.push(nodes['b'], nodes['f'], 100)
    edges.push(nodes['b'], nodes['e'], 4)
    edges.push(nodes['c'], nodes['e'], 10)
    edges.push(nodes['c'], nodes['g'], 6)
    edges.push(nodes['d'], nodes['i'], 4)
    edges.push(nodes['e'], nodes['f'], 8)
    edges.push(nodes['e'], nodes['c'], 1)
    edges.push(nodes['g'], nodes['e'], 7)
    edges.push(nodes['i'], nodes['k'], 1)
    edges.push(nodes['i'], nodes['j'], 2)

    print(list(astar(edges, nodes['a'], nodes['f'])))

    