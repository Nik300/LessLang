# LessLang 0.2
## Project State
The project is in an early stage and is not ready for practical usage.
### What's ready
#### Runtime
The runtime is almost ready. Objects and types work as expected, operators work and objects can be invoked as well.<br/>
In the runtime is also present a Garbage Collector. I also expect to implement a cache for objects, in order to ease the weight on both processor and RAM.<br/>
Math expressions are addressed in the Statement Parser.
#### Statement Parser
The statement parser is currently undergoing thinking process and is being structured.<br/>
It will support variable, function and type declarations as well as math expressions and operations between constants.
### Division
The project is divided into three main sections: <br/>
Section          | Working Status
---------------- | --------------------
Runtime          | 📍 Milestone 2
Statement Parser | ⚒️ Work in Progress
Parser           | ⌚ Planned

## How to build
### Unix systems (Linux/macOS)
This is currently the only options to try out the runtime.<br/>
First install these dependencies:<br/>
Dependency         | Required | Link
------------------ | -------- | -----------------------------------------------
build-essentials   | YES      |
gcc, g++ compilers | YES      |
VS Code            | NO       | [here](https://code.visualstudio.com/download)
make               | YES      |
git                | NO       |

Next, build one of the tests as follows:
`make tests/<test name>` <br/>
For instance, consider the test named "union" under tests/union.cpp, I'd run it like this:
`make tests/union`
and that's it <br/>
## Code Samples
Here are some code samples I've been desingin for a while now:
### Hello World!
```typescript
message: string = "Hello, World!";
main(args: [string]): void {
  sys.println("message:", message);
}
```
The output to this code should be: <br/>
`message: Hello, World!`
### Module
#### import
```typescript
-> console;
main(args: [string]): void {
  console.writeln("Hello!");
}
```
The `->` symbol works as an `import` keyword
#### export
```typescript
<- test;
^fn(): string {
  return "Hello!";
}
^variable: Const<integer> = 5;
```
The symbol `<-` is used to declare the export name of a certain module.<br/>
The prefix `^` exports the related object.
## Contributing
Please feel free to report issues and post PRs if anything looks off to you, and don't hesitate contacting me if you want to contribute to the project at any time.