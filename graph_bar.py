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
  def draw_vs(self, line):
    """Draw bar graph"""
    horizontal_labels, vertical_label, files_in, graph_name, divisor = line.split()
    horizontal_labels_list = horizontal_labels.split(",")
    vertical_values_list = []
    for file in self.importer.files(files_in):
      for line in self.importer.file_in_lines(open(file)):
        if vertical_label not in line:
          continue
        label, value = line.split()
        vertical_values_list.append(float(value) / float(divisor))
    horizontal = self.np.arange(len(horizontal_labels_list))
    self.plt.bar(horizontal, vertical_values_list)
    self.plt.xticks(horizontal + 0.5, horizontal_labels_list, rotation = 0)
    fig = self.plt.gcf()
    fig.savefig(graph_name + ".png", dpi = 100)
  def draw_line(self, line):
    """Draw line graph"""
    styles = ['r-', 'b-', 'g-']
    horizontal_label, vertical_label, paths, names = line.split()
    paths_list = paths.split(",")
    names_list = names.split(",")
    to_read = []
    horizontal_values = []
    vertical_values = {}
    count = 0
    for path in paths_list:
      for name in names_list:
        to_read.append({"path": path + name, "group": count})
      count += 1
    # find paths
    count = 0
    for path in to_read:
      if count >= len(paths_list): break
      for file in self.importer.files(path["path"]):
        for line in self.importer.file_in_lines(open(file)):
          if horizontal_label not in line: continue
          this_label, value = line.split()
          horizontal_values.append(value)
      count += 1
    # read x values (horizontal)
    for path in to_read:
      for file in self.importer.files(path["path"]):
        for line in self.importer.file_in_lines(open(file)):
          if vertical_label not in line: continue
          this_label, value = line.split()
          if paths_list[path["group"]] in vertical_values:
            vertical_values[paths_list[path["group"]]].append(value)
          else:
            vertical_values[paths_list[path["group"]]] = [value]
    # read y values (vertical)
    print horizontal_values
    count = 0
    for path in vertical_values:
      print vertical_values[path]
      self.plt.plot(horizontal_values, vertical_values[path], styles[count])
      count += 1
    self.plt.show()