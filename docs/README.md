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
    B --> D((Arg)):::arg
    B --> E((Redir)):::redir
    E --> EL((Arg)):::arg
    E --> ER((Redir)):::redir
    ER --> EER((Arg)):::arg
    ER --> EEL((CMD)):::cmd
    C --> F((Redir)):::redir
    F --> FL((Arg)):::arg
    F --> FR((Redir)):::redir
    FR --> FFR((Arg)):::arg
    FR --> FFL(... Redirs ...):::redir
    FFL --> FFFL((Redir)):::redir
    FFFL --> FFFR((Arg)):::arg
    FFFL --> FFFFL((CMD)):::cmd
    C --> G(... Pipes ...):::pipe
    G --> H((Pipe)):::pipe
    H --> HL((Redir)):::redir
    HL --> HR((Arg)):::arg
    H --> I((Redir)):::redir
    I --> IR((Arg)):::arg
    I --> IL(... Redirs ...):::redir
    IL --> IIL((CMD)):::cmd
    HL --> HHL(... Redirs ...):::redir
    HHL --> HHHL((CMD)):::cmd
    classDef pipe stroke:#f00
    classDef arg stroke:#0f0
    classDef cmd stroke:#ff0
    classDef redir stroke:#0ff
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
