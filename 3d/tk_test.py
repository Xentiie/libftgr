import tkinter as tk

root = tk.Tk()
root.geometry("100x100")

tk.Label(root, text="a", background="red").pack(expand=False, fill="none", side="top")
tk.Label(root, text="g", background="gray").pack(expand=False, fill="none", side="top")
tk.Label(root, text="b", background="blue").pack(expand=True, fill="y", side="right")
tk.Label(root, text="f", background="yellow").pack(expand=False, fill="x", side="right")
cols = ["gray", "black", "white", "yellow", "green"]
for i in range(3):
	free = tk.Label(root, text="free", background=cols[i])
	free.pack(expand=True, fill="both", side="top")
tk.Label(root, text="c", background="blue").pack(expand=True, fill="y", side="right")

root.mainloop()
