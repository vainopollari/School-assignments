var all_elem = document.querySelectorAll('li')
all_elem.forEach((Element) => {
    if(Element.querySelectorAll('li').length > 0) {
        var number = Element.querySelectorAll('li').length;
        Element.firstChild.nodeValue = Element.firstChild.nodeValue + '(' + number + ')' ;
    }
});
