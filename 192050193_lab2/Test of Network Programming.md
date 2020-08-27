# Test of Network Programming

1. Representational state transfer (REST) is a style of software architecture. As described in a dissertation by Roy Fielding, REST is an "architectural style" that basically exploits the existing technology and protocols of the Web. RESTful is typically used to refer to web services implementing such an architecture.
   RESTful is typically used to refer to web services implementing such an architecture. REST is a style of software architecture. REST" is an architectural paradigm. "RESTful" describes using that paradigm.

2. An idempotent HTTP method is a HTTP method that can be called many times without different outcomes. It would not matter if the method is called only once, or ten times over. The result should be the same. Again, this only applies to the result, not the resource itself. This still can be manipulated (like an update-timestamp, provided this information is not shared in the (current) resource representation.

   OPTIONS

   GET 

   HEAD

3. The three phases are: Mounting, Updating, and Unmounting.

   Mounting means putting elements into the DOM.
   React has four built-in methods that gets called, in this order, when mounting a component:
   constructor()
   getDerivedStateFromProps()
   render()
   componentDidMount()
   The render() method is required and will always be called, the others are optional and will be called if you define them.

   Updating
   The next phase in the lifecycle is when a component is updated.
   A component is updated whenever there is a change in the component's state or props.
   React has five built-in methods that gets called, in this order, when a component is updated:
   getDerivedStateFromProps()
   shouldComponentUpdate()
   render()
   getSnapshotBeforeUpdate()
   componentDidUpdate()
   The render() method is required and will always be called, the others are optional and will be called if you define them.

   Unmounting
   The next phase in the lifecycle is when a component is removed from the DOM, or unmounting as React likes to call it.
   React has only one built-in method that gets called when a component is unmounted:
   componentWillUnmount()
   The componentWillUnmount method is called when the component is about to be removed from the DOM.

4. AJAX = Asynchronous JavaScript And XML.AJAX allows web pages to be updated asynchronously by exchanging data with a web server behind the scenes. This means that it is possible to update parts of a web page, without reloading the whole page.
   An async function can contain an await expression, that pauses the execution of the function and waits for the passed Promise's resolution, and then resumes the async function's execution and returns the resolved value.



The Promise object represents the eventual completion (or failure) of an asynchronous operation, and its resulting value.

A Promise is in one of these states:
pending: initial state, neither fulfilled nor rejected.
fulfilled: meaning that the operation completed successfully.
rejected: meaning that the operation failed.

A pending promise can either be fulfilled with a value, or rejected with a reason (error). When either of these options happens, the associated handlers queued up by a promise's then method are called. If the promise has already been fulfilled or rejected when a corresponding handler is attached, the handler will be called, so there is no race condition between an asynchronous operation completing and its handlers being attached.



the async/await pattern is a syntactic feature of many programming languages that allows an asynchronous, non-blocking function to be structured in a way similar to an ordinary synchronous function. It is semantically related to the concept of a coroutine and is often implemented using similar techniques, and is primarily intended to provide opportunities for the program to execute other code while waiting for a long-running, asynchronous task to complete, usually represented by promises or similar data structures.

