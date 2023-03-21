from typing import List, Tuple, Union
import os
import sys
import argparse
from enum import Enum
from collections import deque

from PyQt6 import QtCore, QtGui, QtWidgets

MAP_HEADER = """\
NO ./bonus/assets/tech.xpm42
SO ./bonus/assets/tech.xpm42
WE ./bonus/assets/tech.xpm42
EA ./bonus/assets/tech.xpm42

F 50,30,30
C 180,180,255

"""


class CellType(Enum):
    EMPTY = QtCore.Qt.GlobalColor.white
    WALL = QtCore.Qt.GlobalColor.black
    DOOR = QtCore.Qt.GlobalColor.darkGray
    START = QtCore.Qt.GlobalColor.green
    MONSTER = QtCore.Qt.GlobalColor.red
    END = QtCore.Qt.GlobalColor.blue


class Grid:
    def __init__(self, width: int, height: int) -> None:
        self._grid = [[] for _ in range(height)]
        self.width = width
        self.height = height

    def __getitem__(self, key: int) -> List[CellType]:
        return self._grid[key]

    def __setitem__(self, key: int, value: List[CellType]) -> None:
        self._grid[key] = value


class Cell(QtWidgets.QGraphicsRectItem):
    SIZE = 20

    type = CellType.EMPTY
    is_outside = False

    def __init__(self, x: int, y: int) -> None:
        super().__init__(x * self.SIZE, y * self.SIZE, self.SIZE, self.SIZE)
        self.setPen(QtGui.QPen(QtCore.Qt.GlobalColor.black))
        self.setBrush(QtGui.QBrush(self.type.value))

    def mousePressEvent(self, event: QtWidgets.QGraphicsSceneMouseEvent) -> None:
        if event.button() == QtCore.Qt.MouseButton.LeftButton and self.scene().parent().dragMode() == QtWidgets.QGraphicsView.DragMode.NoDrag:
            if self.type == CellType.START and self.scene().parent()._click_type != CellType.START:
                self.scene().parent()._start_nb -= 1
            elif self.type != CellType.START and self.scene().parent()._click_type == CellType.START:
                self.scene().parent()._start_nb += 1

            if self.type == CellType.END and self.scene().parent()._click_type != CellType.END:
                self.scene().parent()._end_nb -= 1
            elif self.type != CellType.END and self.scene().parent()._click_type == CellType.END:
                self.scene().parent()._end_nb += 1

            self.type = self.scene().parent()._click_type
            self.setBrush(QtGui.QBrush(self.type.value))

            self.scene().parent().update_map()

    def set_is_outside(self, is_outside: bool) -> None:
        self.is_outside = is_outside
        if self.is_outside:
            self.setBrush(QtGui.QBrush(QtGui.QColor(self.type.value).darker()))
        else:
            self.setBrush(QtGui.QBrush(self.type.value))


class Window(QtWidgets.QGraphicsView):
    outfile = None

    def __init__(self, width: int, height: int) -> None:
        super().__init__()
        self.setRenderHint(QtGui.QPainter.RenderHint.Antialiasing)
        self.setScene(QtWidgets.QGraphicsScene(self))

        self._zoom = 0
        self._drag_start = False
        self._click_type = CellType.WALL
        self._start_nb = 0
        self._end_nb = 0

        self.grid = Grid(width, height)
        self.fill_grid()

        self.initUI()

    def initUI(self) -> None:
        self.setMinimumSize(400, 400)
        self.resize(800, 800)
        self.setWindowTitle("Map Designer")

        self.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        self.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarPolicy.ScrollBarAlwaysOff)

        self._buttons = []
        for type in CellType:
            button = QtWidgets.QPushButton(type.name.title(), self)
            button.clicked.connect(lambda _, t=type: self.switch_type(t))
            self._buttons.append(button)

        self.save_button = QtWidgets.QPushButton("Save", self)
        self.save_button.clicked.connect(self.save_map)
        self.save_button.move(10, 10)

        self.save_as_button = QtWidgets.QPushButton("Save as", self)
        self.save_as_button.clicked.connect(lambda: self.save_map(True))
        self.save_as_button.move(10, 40)

        QtGui.QShortcut(QtGui.QKeySequence("Ctrl+S"), self, lambda: self.save_button.animateClick())
        QtGui.QShortcut(QtGui.QKeySequence("Ctrl+Shift+S"), self, lambda: self.save_as_button.animateClick())
        for index, button in enumerate(self._buttons):
            QtGui.QShortcut(QtGui.QKeySequence(str(index + 1)), self, lambda btn=button: btn.animateClick())

    def switch_type(self, cell_type: CellType) -> None:
        self._click_type = cell_type

    def fill_grid(self) -> None:
        for x in range(self.grid.width):
            for y in range(self.grid.height):
                self.grid[y].append(Cell(x, y))
                self.scene().addItem(self.grid[y][x])

    def is_empty_line(self, line: str) -> bool:
        return all(c == "0" or c == " " for c in line)

    def save_map(self, force_outfile: bool = False) -> None:
        if self._start_nb != 1:
            QtWidgets.QMessageBox.warning(self, "Error", "There must be exactly one start")
            return

        if self._end_nb != 1:
            QtWidgets.QMessageBox.warning(self, "Error", "There must be exactly one end")
            return

        flooded = self.flood_map()
        if not flooded:
            QtWidgets.QMessageBox.warning(self, "Error", "Map is not closed")
            return

        save = ["" for _ in range(self.grid.height)]
        for x in range(self.grid.width):
            for y in range(self.grid.height):
                if self.grid[y][x].type == CellType.START:
                    save[y] += "N"
                elif self.grid[y][x].type == CellType.MONSTER:
                    save[y] += "M"
                elif self.grid[y][x].type == CellType.WALL:
                    save[y] += "1"
                elif self.grid[y][x].type == CellType.DOOR:
                    save[y] += "D"
                elif self.grid[y][x].type == CellType.END:
                    save[y] += "Z"
                elif flooded[y][x]:
                    save[y] += "0"
                else:
                    save[y] += " "

        while self.is_empty_line(save[0]):
            save.pop(0)
        while self.is_empty_line(save[-1]):
            save.pop(-1)
        while self.is_empty_line("".join([s[0] for s in save])):
            save = [s[1:] for s in save]
        while self.is_empty_line("".join([s[-1] for s in save])):
            save = [s[:-1] for s in save]

        if self.outfile is None or force_outfile:
            self.outfile = QtWidgets.QFileDialog.getSaveFileName(self, "Save map", "", "Map file (*.cub)")[0]
            if self.outfile == "":
                QtWidgets.QMessageBox.warning(self, "Error", "No file selected")
                return

        with open(self.outfile, "w") as file:
            file.write(MAP_HEADER + "\n".join(save) + "\n")

    def flood_map(self) -> Union[List[List[bool]], None]:
        bactrack = [[False for _ in range(self.grid.width)] for _ in range(self.grid.height)]
        queue = deque([self.get_start()])
        while queue:
            x, y = queue.popleft()
            if x < 0 or x >= self.grid.width or y < 0 or y >= self.grid.height:
                return False
            if bactrack[y][x] or self.grid[y][x].type == CellType.WALL or self.grid[y][x].type == CellType.END:
                continue

            bactrack[y][x] = True
            queue.append((x + 1, y))
            queue.append((x - 1, y))
            queue.append((x, y + 1))
            queue.append((x, y - 1))
        return bactrack

    def get_start(self) -> Union[Tuple[int, int], None]:
        for x in range(self.grid.width):
            for y in range(self.grid.height):
                if self.grid[y][x].type == CellType.START:
                    return x, y
        return None

    def update_map(self) -> None:
        if self._start_nb != 1:
            for x in range(self.grid.width):
                for y in range(self.grid.height):
                    self.grid[y][x].set_is_outside(False)
            return

        flooded = self.flood_map()
        if flooded:
            for x in range(self.grid.width):
                for y in range(self.grid.height):
                    self.grid[y][x].set_is_outside(not flooded[y][x])
        else:
            for x in range(self.grid.width):
                for y in range(self.grid.height):
                    self.grid[y][x].set_is_outside(False)

    def wheelEvent(self, event: QtGui.QWheelEvent) -> None:
        if event.angleDelta().y() > 0:
            self.scale(1.25, 1.25)
            self._zoom += 1
        elif self._zoom > 0:
            self.scale(0.8, 0.8)
            self._zoom -= 1

    def resizeEvent(self, event: QtGui.QResizeEvent) -> None:
        self.scale(1.25 ** self._zoom, 1.25 ** self._zoom)
        self._zoom = 0
        self.fitInView(self.scene().sceneRect(), QtCore.Qt.AspectRatioMode.KeepAspectRatio)
        for index, button in enumerate(self._buttons):
            button.move(self.width() - 90, 10 + index * 30)

    def mouseMoveEvent(self, event: QtGui.QMouseEvent):
        if event.buttons() == QtCore.Qt.MouseButton.RightButton:
            if not self._drag_start:
                self._drag_start = True
                self.setDragMode(self.DragMode.ScrollHandDrag)
                super().mousePressEvent(
                    QtGui.QMouseEvent(
                        QtCore.QEvent.Type.MouseButtonPress, event.position(),
                        QtCore.Qt.MouseButton.LeftButton,
                        QtCore.Qt.MouseButton.NoButton,
                        QtCore.Qt.KeyboardModifier.NoModifier
                    )
                )

        super().mouseMoveEvent(event)

    def mouseReleaseEvent(self, event: QtGui.QMouseEvent):
        if event.button() == QtCore.Qt.MouseButton.RightButton:
            if self._drag_start:
                self._drag_start = False
                self.setDragMode(self.DragMode.NoDrag)
            self.setDragMode(self.DragMode.NoDrag)

        super().mouseReleaseEvent(event)


def coordinate(value: str) -> int:
    try:
        int_value = int(value)
    except ValueError as e:
        raise argparse.ArgumentTypeError(f"{value} is not a valid coordinate") from e
    if int_value < 3:
        raise argparse.ArgumentTypeError(f"{value} is too small")
    elif int_value > 100:
        raise argparse.ArgumentTypeError(f"{value} is too big")
    return int_value


def parse_args() -> Tuple[int, int, str]:
    parser = argparse.ArgumentParser()
    parser.add_argument("width", type=coordinate)
    parser.add_argument("height", type=coordinate)
    args = parser.parse_args()
    return args.width, args.height


def main() -> None:
    app = QtWidgets.QApplication([])
    window = Window(*parse_args())
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
