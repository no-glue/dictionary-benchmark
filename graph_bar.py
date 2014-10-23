class GraphBar(object):
  def __init__(self, importer, plt, np):
    self.importer = importer
    # for importing lines
    self.plt = plt
    # for plotting
    self.np = np
    # numpy
  @property
  def importer(self):
    return self._importer
  @importer.setter
  def importer(self, value):
    self._importer = value
  @property
  def plt(self):
    return self._plt
  @plt.setter
  def plt(self, value):
    self._plt = value
  @property
  def np(self):
    return self._np
  @np.setter
  def np(self, value):
    self._np = value
  def draw(self, line):
    """Draw bar graph"""
    horizontal_labels, vertical_label, files_in, graph_name = line.split()
    horizontal_labels_list = horizontal_labels.split(",")
    vertical_values_list = []
    for file in self.importer.files(files_in):
      for line in self.importer.file_in_lines(open(file)):
        if vertical_label not in line:
          continue
        label, value = line.split()
        vertical_values_list.append(float(value))
    horizontal = self.np.arange(len(horizontal_labels_list))
    self.plt.bar(horizontal, vertical_values_list)
    self.plt.xticks(horizontal + 0.5, horizontal_labels_list, rotation = 0)
    fig = self.plt.gcf()
    fig.savefig(graph_name + ".png", dpi = 100)