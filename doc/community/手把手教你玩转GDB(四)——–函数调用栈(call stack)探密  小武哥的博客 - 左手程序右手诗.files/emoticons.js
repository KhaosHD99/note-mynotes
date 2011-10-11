function insertEmoticon(insertStr) {
	var myField;
	if (document.getElementById('comment') && document.getElementById('comment').type == 'textarea') {
		myField = document.getElementById('comment');
	} else {
		return false;
	}

	if(document.selection) {
		myField.focus();
		sel = document.selection.createRange();
		sel.text = insertStr;
		myField.focus();

	} else if (myField.selectionStart || myField.selectionStart == '0') {
		var startPos = myField.selectionStart;
		var endPos = myField.selectionEnd;
		var cursorPos = startPos;
		myField.value = myField.value.substring(0, startPos)
					  + insertStr
					  + myField.value.substring(endPos, myField.value.length);
		cursorPos += insertStr.length;
		myField.focus();
		myField.selectionStart = cursorPos;
		myField.selectionEnd = cursorPos;

	} else {
		myField.value += insertStr;
		myField.focus();
	}
}
