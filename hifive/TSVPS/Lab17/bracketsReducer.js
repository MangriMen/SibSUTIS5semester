const strArr = ("(( [300 x 50] ) * ( [50 x 10] )) * ((( [10 x 100] ) * ( [100 x 20] )) * ( [20 x 250] ))").split("");

let i = 0;
let closingIndex = -1;
while (i < strArr.length) {
    while (i < strArr.length && strArr[i] != ")") { i++; }
    closingIndex = i;
    if (closingIndex === strArr.length) {
        break;
    } 

    while (i > 0 && strArr[i] != "(") { i--; }

    if (strArr[i - 1] === "(" && closingIndex !== -1 && strArr[closingIndex + 1] === ")") {
        strArr[closingIndex] = "-";
        strArr[i] = "-";
        closingIndex = -1;
    } else {
        i = closingIndex + 1;
        closingIndex = -1;
    }

    i++;
}

const finalArr = strArr.filter((curr) => curr !== "-");

console.log(finalArr.join(''))