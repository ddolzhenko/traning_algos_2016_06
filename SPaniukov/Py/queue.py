class Queue:
	def __init__(self):
		self._data = []

	def push(self, x):
		self._data.append(x)

	def pop(self):
		return self._data.pop(0)

	def pop_back(self):
		return self._data.pop()

	def empty(self):
		return len(self._data) == 0

	def __str__(self):
		return str(self._data)