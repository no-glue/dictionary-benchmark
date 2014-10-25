import sys
import glob
import numpy
import matplotlib.pyplot as plt
from importer import Importer
from graph_bar import GraphBar
if __name__ == "__main__":
  print "Main"
  for line in sys.stdin:
    importer = Importer(glob)
    graph_bar = GraphBar(importer, plt, numpy)
    graph_bar.draw_line(line)