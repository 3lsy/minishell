<h1 align="center">
	Minishell
  <img src = "https://github.com/3lsy/minishell/assets/107457733/ab36bb69-86f6-4a46-ac1e-04b160dc9f9a" width = 50> 
</h1>

## Design
There are two main components on a shell:
- **Analyzer**
- **Evaluator**

```mermaid
---
title: Analyzer
---
flowchart LR
    input["INPUT: Raw CMD"]
    analyzer["ANALYZER"]
    output["OUTPUT: Command AST"]
    input --> analyzer
    analyzer --> output
```

```mermaid
---
title: Evaluator
---
flowchart LR
    input["INPUT: Command AST"]
    evaluator["EVALUATOR"]
    output["OUTPUT: CMD execution"]
    input --> evaluator
    evaluator --> output
```

```mermaid
---
title: Command Abstract Syntax Tree (AST)
---
%%{ init: { 'flowchart': { 'curve': 'stepAfter' } } }%%
graph TD
    A((Pipe)):::pipe --> B((Redir)):::redir
    A --> C((Pipe)):::pipe
    B --> D((Filename)):::arg
    B --> E((Redir)):::redir
    E --> EL((Filename)):::arg
    E --> ER((Redir)):::redir
    ER --> EER((Filename)):::arg
    ER --> EEL((CMD)):::cmd
    C --> F((Redir)):::redir
    F --> FL((Filename)):::arg
    F --> FR((Redir)):::redir
    FR --> FFR((Filename)):::arg
    FR --> FFL(... Redirs ...):::redir
    FFL --> FFFL((Redir)):::redir
    FFFL --> FFFR((Filename)):::arg
    FFFL --> FFFFL((CMD)):::cmd
    C --> G(... Pipes ...):::pipe
    G --> H((Pipe)):::pipe
    H --> HL((Redir)):::redir
    HL --> HR((Filename)):::arg
    H --> I((Redir)):::redir
    I --> IR((Filename)):::arg
    I --> IL(... Redirs ...):::redir
    IL --> IIL((CMD)):::cmd
    HL --> HHL(... Redirs ...):::redir
    HHL --> HHHL((CMD)):::cmd
    classDef pipe stroke:#f00
    classDef arg stroke:#0f0
    classDef cmd stroke:#ff0
    classDef redir stroke:#0ff
```

```mermaid
---
title: Simplified Abstract Syntax Tree (AST)
---
%%{ init: { 'flowchart': { 'curve': 'stepAfter' } } }%%
graph TD
    A((Pipe)):::pipe --> B((Redir\nFilename)):::redir
    A --> C((Pipe)):::pipe
    B --> E((Redir\nFilename)):::redir
    E --> ER((Redir\nFilename)):::redir
    ER --> EEL((CMD)):::cmd
    C --> F((Redir\nFilename)):::redir
    F --> FR((Redir\nFilename)):::redir
    FR --> FFL(... Redirs ...):::redir
    FFL --> FFFL((Redir\nFilename)):::redir
    FFFL --> FFFFL((CMD)):::cmd
    C --> G(... Pipes ...):::pipe
    G --> H((Pipe)):::pipe
    H --> HL((Redir\nFilename)):::redir
    H --> I((Redir\nFilename)):::redir
    I --> IL(... Redirs ...):::redir
    IL --> IIL((CMD)):::cmd
    HL --> HHL(... Redirs ...):::redir
    HHL --> HHHL((CMD)):::cmd
    classDef pipe stroke:#f00
    classDef arg stroke:#0f0
    classDef cmd stroke:#ff0
    classDef redir stroke:#0ff
```
We can reduce the AST into a linked list if we include the redirections' linked list as an attribute of a command

```mermaid
---
title: Reduced AST
---
%%{ init: { 'flowchart': { 'curve': 'stepAfter' } } }%%
graph LR
    a((CMD)):::cmd --> b((CMD)):::cmd --> c((...)):::cmd --> d((CMD)):::cmd
    classDef cmd stroke:#ff0
```

```mermaid
%%{ init: { 'flowchart': { 'curve': 'stepAfter' } } }%%
graph TB
    subgraph CMD node
    direction TB
    aa((CMD)):::cmd --> bb((Redir)):::redir -->bbb((Filename)):::arg
    cc-->cccc((...)):::arg
    bb-->cc((Redir)):::redir --> ccc((...)):::redir
    aa-->aaa((arg)):::arg-->arg2((arg)):::arg-->arg3((...)):::arg
    aa-->next((next)):::cmd-->next2((next)):::cmd-->next3((...)):::cmd

    
    classDef arg stroke:#0f0
    classDef cmd stroke:#ff0
    classDef redir stroke:#0ff
    end
```

### Node structure
#### Command
```c
typedef struct s_ast
{
	char		*bin;
	int		ac;
	char		**av;
	t_redir		*redir;
	struct s_ast	*next;
}	t_ast;
```
#### Redirections
```c
typedef struct s_redir
{
	t_byte	id;
	char	*file;
}	t_redir;
```

### Interface
In this *minishell*, the interface is very small and is mostly a tool for the **Analyzer** since it doesn't handle any pointer interaction.
However it does handle:
- A prompt to input a command
- History
- Handles user signals:
  | Key Combination | Signal Name     |
  |-----------------|-----------------|
  | `ctrl-C`        | SIGINT          |
  | `ctrl-D`        | EOF (End of File) |
  | `ctrl-\`        | SIGQUIT         |


### Analyzer
The analyzer takes the command, analyze the *lexic*, *syntax* and *semantic*, and process the data into an **Command AST**, that the **Evaluator** will take and use it to evaluate the command, redirection, pipe, etc.
It handles:
- Lexic Analysis
- Syntax Analysis
- Semantic Analysis
- Quotes
  | Quotes         | Behavior                               |
  |----------------|----------------------------------------|
  | Single quotes  | Prevent interpreting anything inside.  |
  | Double quotes  | Prevent interpreting anything except `$` inside. |
  - Not interpret unclosed quotes
- Translations
  - meta-characters
  - Relative path from command to absolute path
  - Env variables
  - $? *which the evaluator has to save*

### Evaluator
The evaluator takes the **Command AST**, launch the appropriate executable on a child process, handling pipes, signal inheritance, **clean** process management, etc.
- Search and launch executables
  - Based on the `PATH` env variable.
  - Based on an aboslute path
  - Based on builtins commands
- Interpret *redirections* and *pipes*
  | Redirection Symbol | Description                                                    |
  |--------------------|----------------------------------------------------------------|
  | `<`                | Redirects input.                                               |
  | `>`                | Redirects output.                                              |
  | `<<`               | Reads input until a line containing the delimiter is seen.     |
  | `>>`               | Redirects output in append mode.                               |
- Builtins
  | Command           | Option           |
  |-------------------|------------------|
  | `echo`            | `-n`             |
  | `cd`              | Only a relative or absolute path |
  | `pwd`             | No options        |
  | `export`          | No options        |
  | `unset`           | No options        |
  | `env`             | No options or arguments |
  | `exit`            | No options        |

![image](https://github.com/3lsy/minishell/assets/35022933/d887b83f-54b8-4873-9c82-3ec3d275851e)

### Entity Relationship Diagram

```mermaid
---
title: Shell Command Processing Flow
---
erDiagram
    Shell_Command }|--|{ Analyzer : "Analyze"
    Shell_Command }|--|{ Command_AST : "Creates"
    Analyzer }o--o{ Command_AST : "Creates"
    Command_AST }o--|| Evaluator : "Evaluate"
```
