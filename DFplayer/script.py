import tkinter as tk
from tkinter import filedialog
from shutil import copyfile

impo_path = None
expo_path = None


def impo():
    global impo_path
    impo_path = filedialog.askopenfilenames(title="Select file", filetypes=(
        ("mp3 files", "*.mp3"), ("wav files", "*.wav")))
    number_of_songs['text'] = f"{len(impo_path)} songs selected"


def expo():
    global expo_path
    expo_path = filedialog.askdirectory()


def move():
    global impo_path
    global expo_path
    song_names = ""
    for i in range(len(impo_path)):
        song_names += impo_path[i].split("/")[-1]+"\n"
        copyfile(
            impo_path[i], f'{expo_path}/{str(i+1).zfill(3)}.{impo_path[i].split(".")[-1]}')
    # insert code to execute main.py in Audio-FSK-Modulation- directory
    # with the arguments as content in song_names variable
    f = open(expo_path+"/000.txt", "w+")
    f.write(song_names)
    f.close()


root = tk.Tk()
root.geometry("160x100")
root.title('Choose files')

number_of_songs = tk.Label(root, text="0 songs selected", width=20)
number_of_songs.grid(row=0, column=0, columnspan=2)
tk.Button(root, text="Import", width=10, command=impo).grid(row=1, column=0)
tk.Button(root, text="Destination", width=10,
          command=expo).grid(row=1, column=1)
tk.Button(root, text="Move", width=20, command=move).grid(
    row=2, column=0, columnspan=2)

root.mainloop()
