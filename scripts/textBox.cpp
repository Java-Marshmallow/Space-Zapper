#include "../headers/textBox.h"

// Constructor, sets font and text and rectangle
TextBox::TextBox(Font font, std::string text, int fontSize, float x, float y, float margin)
{
    // Set font, size and text
    textBoxFont = font;
    textBoxText = text;
    textBoxFontSize = fontSize;
    // Get text box size based on measure of text
    textBoxSize = MeasureTextEx(textBoxFont, textBoxText.data(), textBoxFontSize, textBoxFontSize/12);
    // Position text box and set its size based on text size and margin
    textBoxRect.x = x;
    textBoxRect.y = y;
    textBoxRect.width = textBoxSize.x + margin*2;
    textBoxRect.height = textBoxSize.y + margin*2;
    // Store margin
    textBoxMargin = margin;
}

// Draw text to screen
void TextBox::DrawText() 
{
    // Convert text to C string and display it based on margin
    DrawTextEx(textBoxFont, textBoxText.data(), Vector2({textBoxRect.x + textBoxMargin, textBoxRect.y + textBoxMargin}), textBoxFontSize, textBoxFontSize/12, WHITE);
}

// Change the text and reset the size based on the new text's measure
void TextBox::SetText(std::string newText)
{
    textBoxText = newText;
    textBoxSize = MeasureTextEx(textBoxFont, textBoxText.data(), textBoxFontSize, textBoxFontSize/12);
    textBoxRect.width = textBoxSize.x + textBoxMargin*2;
    textBoxRect.height = textBoxSize.y + textBoxMargin*2;
}

// Uh I don't use this anywhere but it is possible to check if the text is clicked
bool TextBox::CheckCollision()
{
    if(CheckCollisionPointRec(GetMousePosition(), textBoxRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return true; else return false;
}
