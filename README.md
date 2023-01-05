# LessLang
## Project State
The project is in an early stage and is not ready for actual use.
### What's ready
The runtime is almost ready. Objects and types work as expected, operators can be called between objects and calling works as well.<br/>
Only the math expression evaluator is missing, which i am planning on doing asap to start working on the actual language parser
### Division
The project is divided into two main sections: <br/>
Section | Working Status
------- | ---------------
Runtime | ⭕ Almost done
Parser  | ⌚ Planned

## How to build
### Unix systems (Linux/macOS)
This is currently the only options to try out the runtime.<br/>
First install these dependencies:<br/>
Dependency         | Required
------------------ | --------
build-essentials   |   YES
gcc, g++ compilers |   YES
    VS Code        |   NO
      make         |   YES
      git          |   NO

Next, build one of the tests as follows:
`make tests/<test name>` <br/>
For instance, consider the test named "union" under tests/union.cpp, I'd run it like this:
`make tests/union`
and that's it <br/>
## Contributing
Please feel free to report issues and post PRs if anything looks off to you, and don't hesitate contacting me if you want to contribute to the project at any time.