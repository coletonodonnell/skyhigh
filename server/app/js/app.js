
//call function when user clicks on submit and prevents default submission

// window.addEventListener("DOMContentLoaded", (event) => {
//     const form = document.getElementById('input_form');
//     if (form) {
//         form.addEventListener('submit', function(event) {
//             event.preventDefault();
//             handleInput();
//           });
//     }
// });



// //creating output file
// function handleInput(){
//     //get userInput
//     const org = document.getElementById('org').value;
//     const dest = document.getElementById('dest').value;
//     const toggle = document.getElementById('status').checked ? 1 : 0;

//     //create file content
//     const fileContent = org + '\n' + dest + '\n' + toggle;
    
//     //node.js fs module to write to a file without user downloading file
//     const fs = require('fs');

//     //file name and path
//     const fileName = "selection.out";
//     const filePath = "./" + fileName; //COLETON may need to change this

//     //write to file
//     fs.writeFile(filePath, fileContent, (err)=> {
//         if (err){
//             console.error(err);
//         }else {
//             console.log('Updated selection.out');
//         }
//     });
// }



//Below may be useful---------------------

//OTHER OPTION allow user to choose a file to write to -------------
// //call function when user clicks on submit and prevents default submission

// window.addEventListener("DOMContentLoaded", (event) => {
//     const form = document.getElementById('input_form');
//     if (form) {
//         form.addEventListener('submit', function(event) {
//             event.preventDefault();
//             handleInput();
//           });
//     }
// });


// //creating output file
// async function handleInput(){
//     //get userInput
//     const org = document.getElementById('org').value;
//     const dest = document.getElementById('dest').value;
//     const toggle = document.getElementById('status').checked ? 1 : 0;

//     //create file content
//     const fileContent = org + '\n' + dest + '\n' + toggle;
    
//     let fileHandle;
//     try {
//         fileHandle = await getFile();
//     } catch (error) {
//         fileHandle = await createFile();
//     }

//     const writable = await fileHandle.createWritable();
//     await writable.write(fileContent);
//     await writable.close();
// }

// async function getFile() {
//     const options = { type: 'open-file', accepts: [{ extensions: ['txt'] }] };
//     const fileHandle = await window.showOpenFilePicker(options);
//     return fileHandle[0];
//   }
  
//   async function createFile() {
//     const options = { type: 'save-file', accepts: [{ extensions: ['txt'] }], suggestedName: 'selection' };
//     const fileHandle = await window.showSaveFilePicker(options);
//     const writable = await fileHandle.createWritable();
//     await writable.write('');
//     await writable.close();
//     return fileHandle;
//   }
//OTHER OPTION allow user to choose a file to write to -------------


//-----------------------------------


 // const file = new Blob([fileContent], { type: 'text/plain' });
    // const fileURL = URL.createObjectURL(file);
  
    // const link = document.createElement('a');
    // link.href = fileURL;
    // link.download = 'output.txt';
    // document.body.appendChild(link);
    // link.click();
    // document.body.removeChild(link);
//get the visualization-------------

// src="https://public.tableau.com/javascripts/api/viz_v1.js"
// function initViz() {
//     var containerDiv = document.getElementById("vizContainer"),
//         url = "https://public.tableau.com/views/EpucFinalProject/Dashboard1?:language=en-US&:display_count=n&:origin=viz_share_link",
//         options = {
//             hideTabs: true,
//             onFirstInteractive: function () {
//                 console.log("Run this code when the viz has finished loading.");
//             }
//         };

//     var viz = new tableau.Viz(containerDiv, url, options);
//     // Create a viz object and embed it in the container div.
// }

// var divElement = document.getElementById('viz1682089018786');                   
// var vizElement = divElement.getElementsByTagName('object')[0];                    

// if ( divElement.offsetWidth > 800 ) 
//     { vizElement.style.width='900px';vizElement.style.height='527px';} 
// else if ( divElement.offsetWidth > 500 ) 
//     { vizElement.style.width='900px';vizElement.style.height='527px';} 
//     else 
//     { vizElement.style.width='100%';vizElement.style.height='727px';}                     

// var scriptElement = document.createElement('script');                    
// scriptElement.src = 'https://public.tableau.com/javascripts/api/viz_v1.js';                    
// vizElement.parentNode.insertBefore(scriptElement, vizElement);       


//refresh data----
// {/* <script type="text/javascript">
//     function useVizAPI() {
//           var viz = window.tableau.vizs[0];
//           viz.hide();
//           viz.show();
//           viz.refresh();
//           //viz.revert();
//           //viz.filter({Product: ['Mint', 'Green Tea']});
//      }
//      if (document.addEventListener) {
//              window.addEventListener("load", useVizAPI, false);
//      } else if (document.attachEvent) {
//              window.attachEvent("onload", useVizAPI);
//      }

// setInterval( useVizAPI, 10000);

// </script> */}

// //auto refresh--------------
// function initViz() {
//     var containerDiv = document.getElementById("vizContainer"),
//     url = "https://public.tableau.com/views/EpucFinalProject/Dashboard1?:language=en-US&:display_count=n&:origin=viz_share_link";
//     var viz = new tableau.Viz(containerDiv, url, Options);
// }

// let refreshInterval;

// function refresh(){
//     refreshInterval = setInterval(() => 
//         {viz.refreshDataAsync();}, 5000);
        
//     //clear interval so that it stops after one refresh
//     clearInterval(refreshInterval);
// }

 
// document.getElementById("submit").addEventListener("click", refresh());

