# 📝 CCPROG2 Machine Project  
## Simple Translator (Natural Language Processing Intro)

### 🏫 College of Computer Studies — De La Salle University  
### 📚 Course: CCPROG2 — Programming II

---

# 📖 Introduction

This project is a **Simple Translator**, inspired by introductory concepts in **Natural Language Processing (NLP)** and **Computational Linguistics**.  
The program maintains a lexicon of **language–translation pairs** and allows the user to manage data and perform machine translation of text or files.

It simulates real-world translation systems by storing up to:

- **150 entries**
- **10 language–translation pairs per entry**
- **20 characters max** per language or translation

This project includes:  
✔ Data management  
✔ Searching  
✔ File import/export  
✔ Text translation  
✔ Tokenization  
✔ Menu-driven interface  

---

# 📂 Features Overview

## 🔧 Manage Data Menu

### ➕ Add Entry
- Input a **language–translation** pair
- If entries with that pair exist → show them
- User is asked if they want to create a **new entry**
- Add additional pairs until user stops (max 10)

---

### ➕ Add Translations
- Input a **language–translation** pair
- If no entry exists → prompt user to use *Add Entry*
- If one entry exists → allow adding pairs to that entry
- If multiple entries exist → choose which entry to add to
- Prevent adding if entry already has **10 pairs**

---

### ❌ Delete Entry
- Display all entries
- Choose entry number to delete
- Invalid inputs give error messages
- Entire entry is removed

---

### ❌ Delete Translation
- Select an entry
- Select which translation pair to delete
- If entry has only **one pair**, deleting it removes the entire entry
- Input validation ensures safe deletion

---

### 📄 Display All Entries
- Show entries **one at a time**
- Pairs sorted alphabetically by language (ASCII)
- Entries sorted by presence of **English**
- Navigate via:
  - `N` = next  
  - `P` = previous  
  - `X` = exit view

---

### 🔍 Search Word
- Input a translation (e.g., *mahal*)
- Shows all entries containing that word
- Navigation same as *Display All Entries*

---

### 🔍 Search Translation
- Input **language + translation**
- Shows all entries containing that exact pair

---

### 📤 Export
- Save all entries to a text file
- File format must follow exact required layout
- Filename must be ≤ **30 characters** (including extension)
- Overwrites existing files

---

### 📥 Import
- Load entries from exported text file
- For each entry:
  - User decides to **add** or **skip**
- Does NOT assume entries are sorted in file

---

### 🚪 Exit Manage Data
- Returns to Main Menu
- All unsaved data is cleared  

---

# 🌐 Translate Menu

Before translation begins, the user loads a file (similar to Import).

---

## 🗣 Translate Text Input
- User provides:
  - Source language
  - Text (≤150 chars)
  - Target language
- Tokenizes input (splits by spaces)
- Removes punctuation (.,!?)
- Performs word-level translation
- Unknown words remain unchanged
- If multiple translations exist → first encountered is used
- User may translate multiple texts in a row

---

## 📁 Translate Text File
- User provides:
  - Source language
  - Input filename
  - Target language
  - Output filename
- File may contain multiple sentences
- Sentences end with `.`, `?`, `!`
- Each translated sentence is:
  - Displayed
  - Saved into the output file (one sentence per line)

---

## 🚪 Exit Translate Menu
- Clears loaded translation data
- Returns to Main Menu

---

# 📌 Restrictions (IMPORTANT)

You are **NOT allowed** to use:

- ❌ Global variables  
- ❌ `goto`  
- ❌ `break` or `continue` (except to exit switch cases)  
- ❌ `return` to exit loops prematurely  
- ❌ `exit()` to quit function/menu  
- ❌ Calling `main()` to restart program  

Program must follow:

- `gcc -Wall -std=C99`
- Variables declared at start of functions
- Proper documentation and readable coding style

---

# 🧪 Testing & Submission Requirements

### Must Submit:
- ✔ Source code  
- ✔ Test script (table format, 3 categories per function)  
- ✔ Sample exported text file  
- ✔ Internal documentation with certification header  

### Test cases must cover:
- Valid inputs  
- Edge cases  
- Error handling  

---

# 🗓 Suggested Milestones

| Date | Target |
|------|--------|
| **Feb 28** | Menus, tokenization, data struct setup |
| **Mar 7** | Add Entry, Add Translations, Display, Search |
| **Mar 14** | Delete features, Translate Text Input |
| **Mar 21** | Export, Import, Translate Text File |
| **Mar 28** | Full integration & testing |
| **Mar 31 (0730 AM)** | FINAL DEADLINE |

---

# ⭐ Bonus Features (Optional)
Up to **+10 points** for enhancements such as:

- Multi-word translations  
- Language detection  
- Smarter translation heuristics  

---

# 🎓 Academic Integrity Notice
Any form of cheating, plagiarism, or unauthorized collaboration results in:

⚠ **0.0 for the course**  
⚠ **Disciplinary case**

---

# 📘 End of README




1.) Milestone 1 : February 28 [x]
    
    a. Menu options and transitions
    b. Preliminary outline of functions to be created
    c. Tokenize
    d. Removal of symbols
    e. Declaration of Data Structure needed

2.) Milestone 2: March 7 [x]
    
    a. Add Entry
    b. Add Translations
    c. Display all entries
    d. View Words
    e. Search Word
    f. Search Translation

3.) Milestone 3: March 14 [x]
    
    a. Delete Entry
    b. Delete Translation
    c. Translate Text Input
    +For this feature, do not clear the contents of the array of entries upon exit from Manage Data menu IF you have
    not implemented the import and export yet.

4.) Milestone 4: March 21 [x]
    
    a. Export
    b. Import
    c. Translate Text File

5.) Milestone 5: March 28 [x]
    
    a. Integrated testing (as a whole, not per function/feature)
    b. Collect and verify versions of code and documents that will be uploaded
