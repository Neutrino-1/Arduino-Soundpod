import os
import tkinter as tk
from tkinter import *
from tkinter.ttk import *
from tkinter import filedialog
from shutil import copyfile

impo_path = []
expo_path = str
folder_number = 1
selected_folder = 0
folders = []

def impo():
    global impo_path
    global import_destination_count
    global folders
    global selected_folder
    folder_selection()
    progress['text'] = "Waiting to transfer the files"
    impo_path.append(list(filedialog.askopenfilenames(title="Select file", filetypes=(
        ("mp3 files", "*.mp3"), ("wav files", "*.wav")))))
    
    #number_of_selected_files = 0
    # for each_import in impo_path:
    #     number_of_selected_files += len(each_import)
    # number_of_songs['text'] = f"{number_of_selected_files} songs selected"
    final_path_list = []

    for each_import in impo_path:
        if type(each_import)!= str:
            for each_each_import in each_import:
                final_path_list.append(each_each_import)
        else:
            final_path_list.append(each_import)

    impo_path = []
    if len(folders) > (selected_folder+1):
        folders[selected_folder] += final_path_list
    else:
        list_filler()
        folders[selected_folder] = final_path_list 

    show_folder_content()
    calculate_total_songs()
    

def calculate_total_songs():
    global folders
    total_song_count = 0
    for files in folders:
        total_song_count += len(files)
    number_of_songs['text'] = f'Number of Files : {total_song_count}'

def expo():
    global expo_path
    expo_path = filedialog.askdirectory()
    destination_path['text'] = expo_path

def list_filler():
    global folders
    global selected_folder
    while len(folders) < (selected_folder+1):
        folders.append([])

def remove_file(): 
    selected_file = import_list.curselection()[0]
    del folders[selected_folder][selected_file]
    calculate_total_songs()
    show_folder()

def folder_selection():
    global selected_folder
    selected_folder = folder_list.curselection()[0];
    selection_folder_lable['text'] = f'Selected Folder : {str(selected_folder+1).zfill(2)}';

def move():
    global impo_path
    global expo_path
    song_names = ""
    for j,files in enumerate(folders):
        print(j/len(folders)*250)
        directory = str(j+1).zfill(2)
        parent_dir = expo_path
        path = os.path.join(parent_dir, directory) 
        os.mkdir(path) 
        song_names += "\n"+str(directory)+"\n\n"
        for i,file in enumerate(files):
            song_names += file.split("/")[-1]+"\n"
            copyfile(file, f'{path}/{str(i+1).zfill(3)}.{file.split(".")[-1]}')
    # insert code to execute main.py in Audio-FSK-Modulation- directory
    # with the arguments as content in song_names variable
    f = open(expo_path+"/000.txt", "w+")
    f.write(song_names)
    f.close()
    expo_path = ""
    progress['text'] = "Transfered successfully"

def add_folder(): 
    global folder_number
    folder_number += 1
    folder_list.insert(folder_number, str(folder_number).zfill(2))
    number_of_folders['text'] = f'Number of Folders : {folder_number}'

def remove_folder(): 
    global folder_number
    folder_list.delete(folder_number-1, last=None)
    folder_number -= 1
    number_of_folders['text'] = f'Number of Folders : {folder_number}'

def show_folder_content():
    folder_selection()
    show_folder()

def show_folder():
    global selected_folder
    global folders

    import_list.delete(0,import_list.size())

    if len(folders) < (selected_folder+1):
         list_filler()
         
    if folders[selected_folder] == []:
        import_list.insert(0,"No Files")
    else:
        n = 0
        for files in folders[selected_folder]:
            import_list.insert(n,files.split("/")[-1])
            n += 1     
    
    

root = tk.Tk()
root.geometry("370x355")
root.title('DFPlayer Helper')
root.resizable(height = False, width = False)

tk.Label(root, text="Folders", width=20).grid(pady=5,row=0, column=1,columnspan=2)
selection_folder_lable = tk.Label(root, text="Selected Folder : None", width=20)
selection_folder_lable.grid(pady=5,row=0, column=5,columnspan=2)

folder_list = tk.Listbox(root)  
folder_list.insert(folder_number,str(folder_number).zfill(2))
folder_list.grid(row=1, column=1,padx=0, columnspan=2) 

tk.Button(root, text="Add folder", width=10, command=add_folder).grid(padx = 5,pady=5,row=2, column=1)
tk.Button(root, text="remove", width=10, command=remove_folder).grid(row=2, column=2)

tk.Button(root, text=">>", width=2, command=show_folder_content).grid(row=1, column=3, columnspan=1)

import_list  = tk.Listbox(root) 
import_list.grid(row=1, column=5,padx=10,columnspan=2) 
tk.Button(root, text="Import", width=10, command=impo).grid(padx = 5,pady=5,row=2, column=5)
tk.Button(root, text="remove", width=10, command=remove_file).grid(row=2, column=6)

number_of_songs = tk.Label(root, text=f'Number of Files : 0', width=40)
number_of_songs.grid(pady=5,row=3, column=1, columnspan=6)

number_of_folders = tk.Label(root, text=f'Number of Folders : {folder_number}', width=40)
number_of_folders.grid(pady=5,row=4, column=1, columnspan=6)

tk.Button(root, text="Destination", width=10,command=expo).grid(row=5, column=0,columnspan=2)
destination_path = tk.Label(root, text="destination", width=10)
destination_path.grid(row=5, column=2)

tk.Button(root, text="Move", width=10, command=move).grid(row=6, column=0, columnspan=2,pady = 5)

# Progress bar widget 
progress = tk.Label(root, text='Waiting to transfer the files', width=40)
progress.grid(row=6, column=2,columnspan=5)
root.mainloop()
