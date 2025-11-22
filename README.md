# 🎓 **STUDENT MARKS MANAGEMENT SYSTEM (C Programming)**
  
## 📄 **ABSTRACT**

The **Student Marks Management System** is a terminal-based application written in **C** that helps users efficiently manage student academic records. 
It provides essential operations such as **adding**, **viewing**, **searching**,**updating**, and deleting student mark details.

All student records are stored in a binary file (`marks.txt`) to ensure data persistence across program executions.

This project demonstrates key C programming concepts including **structures**, **file handling**, **arrays**, **loops**, **conditional logic**, and **modular programming**—making it ideal for **academic use**, **beginner projects*8, and **practical learning**.

---

##  ✨ **FEATURES**
### **Core Functionalities**

- ➕ **Add new student mark records** (Roll No, Name, Marks of Subjects)
- 📋 **Display all student records** in a structured table
- 🔍 **Search student by Roll Number**
- ✏️ **Update existing student marks**
- ❌ **Delete student records**
- 💾 Persistent data storage using binary file (`marks.txt`)
- 🖥️ Fully terminal-based, menu-driven interface
- 👨‍💻 Beginner-friendly modular C code
- ⚙️ Auto-creates the data file if it does not exist
- ⚠️ Basic input validation and error handling

  ---

## 🛠️ **TECHNICAL REQUIREMENTS**

## **System Requirements**
- Operating System: **Windows / Linux / macOS**
- Terminal or Command Prompt
- At least **4 MB RAM**
- Minimal disk space for `marks.txt`

## **Software Requirements**
- C Compiler: GCC / MinGW / Clang / MSVC
- Code Editor or IDE: VS Code, Code::Blocks, Dev-C++, etc.
- Optional: Make utility for Makefile builds

## **Programming Requirements**
- Language: **C**
- Standard Supported: **C89 / C99 / C11**
- Required Header Files:
- `stdio.h`
- `stdlib.h`
- `string.h`

## **File Handling**
- Requires Read/Write permissions
- Records stored in binary format (marks.txt)
- File auto-created if missing

---

## 📌 **FUNCTIONAL REQUIREMENTS**

## **User Interface**
- Terminal-based CLI
- Clean, menu-driven navigation
- Validates all user inputs

---

## 🎓 **Student Marks Operations**

## ➕ **Add Student**
- Enter Roll No, Name, Subject Marks
- Stored in marks.txt

### 📋 **Display Students**
- Shows all student details in a formatted table
- Computes total marks and percentage 

## 🔍** Search Student**
- Search using **unique Roll Number**

## ✏️ **Update Student**
- Modify Name, Marks of any subject

## ❌ **Delete Student**
- Permanently remove a record

### 🔧 **DATA MANAGEMENT**
- Binary file ensures fast and safe storage
- Secure updates and deletions
- Handles empty/missing file gracefully

### 🔄 **PROGRAM FLOW**
- Interactive menu runs in a loop
- Clear success and error messages
- Exit option included

---

## ▶️ **Running the Program**

## 1️⃣ Compile
```bash
gcc marks.c -o marks
```

### 2️⃣ Run

**Linux / macOS**

```bash
./marks
```

**Windows**

```bash
marks.exe
```

### 3️⃣ Data File

*Auto-creates marks.txt
*Stores all student mark records in binary format

---
## 📸 **Screenshots (Optional Sections)**

*Add Student

*<img width="383" height="394" alt="Screenshot 2025-11-23 001346" src="https://github.com/user-attachments/assets/53b18daa-b8fb-43bd-b258-34ab39c1bd2b" />


*Display Students

*<img width="791" height="265" alt="Screenshot 2025-11-23 001424" src="https://github.com/user-attachments/assets/3077faed-6ae4-4f38-8057-f8c78f6a989a" />


*Search Student

*<img width="327" height="511" alt="Screenshot 2025-11-23 001459" src="https://github.com/user-attachments/assets/6c84fc41-415b-4738-9217-e1839fa478fa" />


*Update Marks

*<img width="484" height="529" alt="Screenshot 2025-11-23 001621" src="https://github.com/user-attachments/assets/92942d16-46d1-46cb-91ec-f84ac51a6001" />


*Delete Student

*<img width="376" height="268" alt="Screenshot 2025-11-23 001645" src="https://github.com/user-attachments/assets/af452758-a6ef-4d05-b32b-87b1c909d4db" />


*Exit Program

*<img width="314" height="202" alt="Screenshot 2025-11-23 001702" src="https://github.com/user-attachments/assets/316fe2ea-7cfe-4a0d-b1d5-c3ac964850ff" />


##📝 **Author** 

**B. Meganadh Reddy**
