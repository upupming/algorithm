export interface MyNode {
  val: string
  prev: MyNode | null
  next: MyNode | null
}

class TextEditor {
  cursor: MyNode
  constructor () {
    this.cursor = {
      val: '#',
      prev: null,
      next: null
    }
  }

  addText (text: string): void {
    for (const ch of text) {
      const newNode = {
        val: ch,
        prev: this.cursor,
        next: this.cursor.next
      }
      if (this.cursor.next) this.cursor.next.prev = newNode
      this.cursor.next = newNode
      this.cursor = this.cursor.next
    }
  }

  deleteText (k: number): number {
    let cnt = 0
    while (k-- && this.cursor.prev) {
      this.cursor.prev.next = this.cursor.next
      if (this.cursor.next) this.cursor.next.prev = this.cursor.prev
      this.cursor = this.cursor.prev
      cnt++
    }
    return cnt
  }

  getLast10 (): string {
    let p: MyNode | null = this.cursor; let cnt = 10
    const a = []
    while (cnt-- && p && p.val !== '#') {
      a.push(p.val)
      p = p.prev
    }
    return a.reverse().join('')
  }

  cursorLeft (k: number): string {
    while (k-- && this.cursor.prev) {
      this.cursor = this.cursor.prev
    }
    return this.getLast10()
  }

  cursorRight (k: number): string {
    while (k-- && this.cursor.next) {
      this.cursor = this.cursor.next
    }
    return this.getLast10()
  }
}

/**
* Your TextEditor object will be instantiated and called as such:
* var obj = new TextEditor()
* obj.addText(text)
* var param_2 = obj.deleteText(k)
* var param_3 = obj.cursorLeft(k)
* var param_4 = obj.cursorRight(k)
*/
