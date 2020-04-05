import copy
from typing import List, Dict
from math import inf
from collections import defaultdict
from queue import PriorityQueue



class Node:

    def __init__(self, config: List[List[str]], goal: List[List[str]]) -> None:
        self.config = copy.deepcopy(config)
        self.h = heuristic(config, goal)

    def __lt__(self, other):
        return self.h < other.h

    def __repr__(self) -> str:
        return "[\n" + '\n'.join([f"\t{stack}" for stack in self.config]) + "\n]" + f" h = {str(self.h)}"



def heuristic(config: List[List[str]], goal: List[List[str]]) -> int:
    h = 0
    for stack_itr, stack in enumerate(goal):
        for block_itr, block in enumerate(stack):
            if block_itr >= len(config[stack_itr]) or block != config[stack_itr][block_itr]:
                h += 1

    return h


def reconstruct_path(came_from: Dict[Node, Node], current: Node, gscore: Dict[Node, int], fscore: Dict[Node, int]):
    path = [current]

    while current in came_from:
        current = came_from[current]
        path.append(current)

    return reversed(path)


def astar(start: Node, end: Node) -> List[List[str]]:
    open_set = PriorityQueue()
    open_set.put((start.h, start))    #use fscore as priority

    came_from = {}  #will store the whole object as we do not have something like the edge list from the base case

    gscore = defaultdict(lambda: inf)
    gscore[start] = 0

    fscore = defaultdict(lambda: inf)
    fscore[start] = start.h

    while not open_set.empty():
        current = open_set.get()[1]
        if current.config == end.config:
            return reconstruct_path(came_from, current, gscore, fscore)

        #generate possible moves
        #parse every stack and compute every possible move
        for i, istack in enumerate(current.config):
            for j, jstack in enumerate(current.config):
                if istack is jstack or not istack:
                    continue    #ignore empty moves
                
                #generate the move
                dummy = copy.deepcopy(current.config)
                dummy[j].append(dummy[i].pop()) #move the block
                move = Node(dummy, end.config)

                tentative_gscore = gscore[current] + 1   #weight of a move is always 1
                if tentative_gscore < gscore[move]:
                    came_from[move] = current
                    gscore[move] = tentative_gscore
                    fscore[move] = gscore[move] + move.h

                    if move not in [elem[1] for elem in list(open_set.queue)]:
                        open_set.put((fscore[move], move))

    return None


if __name__ == "__main__":

    start = Node([
        ['a'],
        ['b', 'c'],
        ['d'],
    ],
    [
        ['c', 'b'],
        [],
        ['d', 'a'],
    ])

    end = Node([
        ['c', 'b'],
        [],
        ['d', 'a'],
    ],
    [
        ['c', 'b'],
        [],
        ['d', 'a'],
    ])

    print(list(astar(start, end)))