# The memento class stores the past state of the editor.
class Snapshot:
    def __init__(self, text, curX, curY, selectionWidth):
        self._text = text
        self._curX = curX
        self._curY = curY
        self._selectionWidth = selectionWidth

    def __str__(self):
        return f"Text: '{self.text}', Cursor: ({self.curX}, {self.curY}), Selection: {self.selectionWidth}"


# The originator holds some important data that may change over time. It also defines a method for saving its state inside a
# memento and another method for restoring the state from it.
# Originator keeps LCM of snapshots.
class Editor:
    def __init__(self):
        self.text = ""
        self.curX = 0
        self.curY = 0
        self.selectionWidth = 0
    
    def setText(self, text):
        self.text = text
    
    def setCursor(self, x, y):
        self.curX = x
        self.curY = y
    
    def setSelectionWidth(self, width):
        self.selectionWidth = width
    
    # Saves the current state inside a memento.
    def createSnapshot(self):
        # Memento is an immutable object; that's why the originator passes its state to the memento's constructor parameters.
        return Snapshot(self.text, self.curX, self.curY, self.selectionWidth)
    
    # At some point, a previous state of the editor can be restored using a memento object.
    def restore(self, snapshot: Snapshot):
        self.setText(snapshot._text)
        self.setCursor(snapshot._curX, snapshot._curY)
        self.setSelectionWidth(snapshot._selectionWidth)

    def __str__(self):
        return f"Text: '{self.text}', Cursor: ({self.curX}, {self.curY}), Selection: {self.selectionWidth}"


# A command object can act as a caretaker. In that case, the command gets a memento just before it changes the
# originator's state. When undo is requested, it restores the originator's state from a memento.
# Caretaker maintains LCM of Originator.
class MSWord:
    def __init__(self, editor: Editor):
        self.editor = editor
        self.backups = list()
    
    def makeBackup(self):
        self.backups.append(self.editor.createSnapshot())
    
    def undo(self):
        if len(self.backups) > 0:
            snapshot: Snapshot = self.backups.pop()
            self.editor.restore(snapshot)


# Client code
if __name__ == "__main__":
    editor = Editor()
    word_app = MSWord(editor)
    
    # Initial state
    editor.setText("Hello")
    editor.setCursor(5, 0)
    editor.setSelectionWidth(0)
    print(f"Initial state: {editor}")
    
    # Make backup before changes
    word_app.makeBackup()
    
    # Make changes
    editor.setText("Hello World")
    editor.setCursor(11, 0)
    editor.setSelectionWidth(5)
    print(f"After changes: {editor}")
    
    # Undo to restore previous state
    word_app.undo()
    print(f"After undo: {editor}")
