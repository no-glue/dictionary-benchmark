class Importer(object):
  def __init__(self, glob):
    self.glob = glob
  @property
  def glob(self):
      return self._glob
  @glob.setter
  def glob(self, value):
      self._glob = value
  def files(self, path):
    """Get files to read"""
    return self.glob.glob(path)
  def file_in_lines(self, file_object):
    """Read file in lines"""
    with file_object as f:
      for line in f.readlines():
        yield line