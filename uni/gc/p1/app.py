
import sys
import melkman
import matplotlib.pyplot as plt



polyline = [melkman.Point([int(val) for val in pair.split(' ')]) for pair in open(sys.argv[1], 'r').read().splitlines()]

sol = melkman.do_melkman(polyline)

ax1 = plt.subplot(121)
ax1.plot([p.x for p in polyline], [p.y for p in polyline], marker = 'o', markersize = 4, markerfacecolor = 'red')
ax1.plot([polyline[0].x, polyline[-1].x], [polyline[0].y, polyline[-1].y])

ax2 = plt.subplot(122, sharex = ax1, sharey = ax1)
ax2.plot([p.x for p in sol], [p.y for p in sol], marker = 'o', markersize = 4, markerfacecolor = 'red')
plt.show()

# 0 0
# 1 1
# 1 2
# 0 3
# -1 2
# 0 2
# 3 1
# 4 8
# 9 3
# 1 1
# 2 2
# 3 3