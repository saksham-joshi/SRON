const vscode = require("vscode");

// ─── All Built-in Keywords ───
const KEYWORDS = [
  "Any", "and", "args", "Bool", "Bool_s", "break",
  "Char", "Char_s", "condition", "console", "continue",
  "Double", "Double_s", "elif", "else",
  "FileReader", "FileReader_s", "FileWriter", "FileWriter_s",
  "false", "for", "foreach", "free",
  "Int", "Int_s", "if",
  "List", "List_s", "linux", "lsft",
  "Main", "name", "not", "on", "or",
  "OBUFFER", "PI", "range", "return", "rotate", "rsft",
  "String", "String_s", "true", "type", "Void",
  "while", "windows", "xor"
];

// ─── Compile-time Constants ───
const CONSTANTS = [
  "ArgumentException",
  "CLI_COLOR_BLACK", "CLI_COLOR_RED", "CLI_COLOR_GREEN", "CLI_COLOR_YELLOW",
  "CLI_COLOR_BLUE", "CLI_COLOR_MAGENTA", "CLI_COLOR_CYAN", "CLI_COLOR_WHITE",
  "CLI_COLOR_BRIGHT_BLACK", "CLI_COLOR_BRIGHT_RED", "CLI_COLOR_BRIGHT_GREEN",
  "CLI_COLOR_BRIGHT_YELLOW", "CLI_COLOR_BRIGHT_BLUE", "CLI_COLOR_BRIGHT_MAGENTA",
  "CLI_COLOR_BRIGHT_CYAN", "CLI_COLOR_BRIGHT_WHITE",
  "CLI_DESIGN_BG_BRIGHT_BLACK", "CLI_DESIGN_BG_BRIGHT_BLUE", "CLI_DESIGN_BG_BRIGHT_CYAN",
  "CLI_DESIGN_BG_BRIGHT_GREEN", "CLI_DESIGN_BG_BRIGHT_MAGENTA", "CLI_DESIGN_BG_BRIGHT_RED",
  "CLI_DESIGN_BG_BRIGHT_WHITE", "CLI_DESIGN_BG_BRIGHT_YELLOW",
  "CLI_DESIGN_BG_BLACK", "CLI_DESIGN_BG_BLUE", "CLI_DESIGN_BG_CYAN",
  "CLI_DESIGN_BG_GREEN", "CLI_DESIGN_BG_MAGENTA", "CLI_DESIGN_BG_RED",
  "CLI_DESIGN_BG_WHITE", "CLI_DESIGN_BG_YELLOW",
  "CLI_DESIGN_BLINK", "CLI_DESIGN_BLINK_FAST", "CLI_DESIGN_BOLD",
  "CLI_DESIGN_DIM", "CLI_DESIGN_HIDDEN", "CLI_DESIGN_ITALIC",
  "CLI_DESIGN_RESET", "CLI_DESIGN_STRIKE", "CLI_DESIGN_UNDERLINE",
  "DivisionByZeroException", "IndexNotWithinRangeException", "InputTypeException",
  "PI", "SRON_CMD_GC_STACK_LEN", "SRON_CMD_IS_BYTECODE_CACHED",
  "SRON_CMD_IS_FILE_AVAILABLE", "SRON_CMD_IS_OBUFFER_EMPTY",
  "SRON_CMD_NO_OF_BYTECODE_CACHED", "SRON_CMD_OBUFFER_CLEAR",
  "SRON_CMD_SIZEOF_OBUFFER"
];

// ─── Type Keywords ───
const TYPES = [
  "Any", "Bool", "Char", "Double", "FileReader", "FileWriter",
  "Int", "List", "LiteralString", "String", "Void"
];

// ─── Built-in Functions ───
const FUNCTIONS = [
  // print
  { name: "print", detail: "Print data to terminal", insertText: "print($0)" },
  { name: "println", detail: "Print data to terminal with newline", insertText: "println($0)" },
  // input
  { name: "inputInt", detail: "Read Int from terminal", insertText: "inputInt($0)" },
  { name: "inputDouble", detail: "Read Double from terminal", insertText: "inputDouble($0)" },
  { name: "inputChar", detail: "Read Char from terminal", insertText: "inputChar($0)" },
  { name: "inputString", detail: "Read String from terminal", insertText: "inputString($0)" },
  // type conversion
  { name: "toBool", detail: "Convert to Bool", insertText: "toBool($0)" },
  { name: "toDouble", detail: "Convert to Double", insertText: "toDouble($0)" },
  { name: "toInt", detail: "Convert to Int", insertText: "toInt($0)" },
  { name: "toString", detail: "Convert to String", insertText: "toString($0)" },
  // type check
  { name: "isVoid", detail: "Check if value is Void", insertText: "isVoid($0)" },
  { name: "isInt", detail: "Check if value is Int", insertText: "isInt($0)" },
  { name: "isDouble", detail: "Check if value is Double", insertText: "isDouble($0)" },
  { name: "isChar", detail: "Check if value is Char", insertText: "isChar($0)" },
  { name: "isBool", detail: "Check if value is Bool", insertText: "isBool($0)" },
  { name: "isCollective", detail: "Check if value is Collective", insertText: "isCollective($0)" },
  { name: "isString", detail: "Check if value is String", insertText: "isString($0)" },
  { name: "isList", detail: "Check if value is List", insertText: "isList($0)" },
  { name: "isFileReader", detail: "Check if value is FileReader", insertText: "isFileReader($0)" },
  { name: "isFileWriter", detail: "Check if value is FileWriter", insertText: "isFileWriter($0)" },
  { name: "isLiteralString", detail: "Check if value is LiteralString", insertText: "isLiteralString($0)" },
  // math
  { name: "abs", detail: "Absolute value", insertText: "abs($0)" },
  { name: "cbrt", detail: "Cube root", insertText: "cbrt($0)" },
  { name: "ceil", detail: "Ceiling (round up)", insertText: "ceil($0)" },
  { name: "cos", detail: "Cosine (radians)", insertText: "cos($0)" },
  { name: "floor", detail: "Floor (round down)", insertText: "floor($0)" },
  { name: "log", detail: "Natural logarithm", insertText: "log($0)" },
  { name: "log2", detail: "Base-2 logarithm", insertText: "log2($0)" },
  { name: "log10", detail: "Base-10 logarithm", insertText: "log10($0)" },
  { name: "max", detail: "Maximum value", insertText: "max($0)" },
  { name: "min", detail: "Minimum value", insertText: "min($0)" },
  { name: "sin", detail: "Sine (radians)", insertText: "sin($0)" },
  { name: "sqrt", detail: "Square root", insertText: "sqrt($0)" },
  { name: "tan", detail: "Tangent (radians)", insertText: "tan($0)" },
  // char
  { name: "ascii", detail: "Get ASCII value of char", insertText: "ascii($0)" },
  { name: "isAlphabet", detail: "Check if char is an alphabet", insertText: "isAlphabet($0)" },
  { name: "isAlphaNum", detail: "Check if char is alphanumeric", insertText: "isAlphaNum($0)" },
  { name: "isConsonant", detail: "Check if char is a consonant", insertText: "isConsonant($0)" },
  { name: "isDigit", detail: "Check if char is a digit", insertText: "isDigit($0)" },
  { name: "isLower", detail: "Check if char is lowercase", insertText: "isLower($0)" },
  { name: "isUpper", detail: "Check if char is uppercase", insertText: "isUpper($0)" },
  { name: "isVowel", detail: "Check if char is a vowel", insertText: "isVowel($0)" },
  { name: "toLower", detail: "Convert char to lowercase", insertText: "toLower($0)" },
  { name: "toUpper", detail: "Convert char to uppercase", insertText: "toUpper($0)" },
  // file
  { name: "freader", detail: "Open file for reading", insertText: "freader($0)" },
  { name: "fwriter", detail: "Open file for writing", insertText: "fwriter($0)" },
  { name: "fclose", detail: "Close a file", insertText: "fclose($0)" },
  { name: "fisOpen", detail: "Check if file is open", insertText: "fisOpen($0)" },
  { name: "fisEnd", detail: "Check if file reached end", insertText: "fisEnd($0)" },
  { name: "fgetName", detail: "Get file name", insertText: "fgetName($0)" },
  { name: "freset", detail: "Reset file cursor", insertText: "freset($0)" },
  { name: "fcurPos", detail: "Get current file cursor position", insertText: "fcurPos($0)" },
  { name: "fsetSeek", detail: "Set file cursor position", insertText: "fsetSeek($0)" },
  { name: "freadChar", detail: "Read a char from file", insertText: "freadChar($0)" },
  { name: "freadLine", detail: "Read a line from file", insertText: "freadLine($0)" },
  { name: "freadWhole", detail: "Read entire file content", insertText: "freadWhole($0)" },
  { name: "fwriteChar", detail: "Write a char to file", insertText: "fwriteChar($0)" },
  { name: "fwriteString", detail: "Write a string to file", insertText: "fwriteString($0)" },
  // list / string
  { name: "at", detail: "Get element at index", insertText: "at($0)" },
  { name: "clear", detail: "Clear all elements", insertText: "clear($0)" },
  { name: "count", detail: "Count occurrences", insertText: "count($0)" },
  { name: "delete", detail: "Delete element at index", insertText: "delete($0)" },
  { name: "index", detail: "Find first index of element", insertText: "index($0)" },
  { name: "insert", detail: "Insert element at index", insertText: "insert($0)" },
  { name: "len", detail: "Get length", insertText: "len($0)" },
  { name: "push", detail: "Push element to end", insertText: "push($0)" },
  { name: "pop", detail: "Remove last element", insertText: "pop($0)" },
  { name: "replace", detail: "Replace element", insertText: "replace($0)" },
  { name: "reverse", detail: "Reverse elements", insertText: "reverse($0)" },
  { name: "reverseSort", detail: "Sort in reverse order", insertText: "reverseSort($0)" },
  { name: "rindex", detail: "Find last index of element", insertText: "rindex($0)" },
  { name: "sort", detail: "Sort elements", insertText: "sort($0)" },
  { name: "split", detail: "Split string", insertText: "split($0)" },
  { name: "subPart", detail: "Get sub-part", insertText: "subPart($0)" },
  { name: "update", detail: "Update element at index", insertText: "update($0)" },
  { name: "trim", detail: "Trim whitespace", insertText: "trim($0)" },
  // miscellaneous
  { name: "beep", detail: "Make a beep sound (freq, duration)", insertText: "beep($0)" },
  { name: "cliTextColor", detail: "Set CLI text color (R, G, B)", insertText: "cliTextColor($0)" },
  { name: "cliBgColor", detail: "Set CLI background color (R, G, B)", insertText: "cliBgColor($0)" },
  { name: "copy", detail: "Create a deep copy", insertText: "copy($0)" },
  { name: "exit", detail: "Exit program with code", insertText: "exit($0)" },
  { name: "getExecTime", detail: "Get execution time in ms", insertText: "getExecTime()" },
  { name: "randInt", detail: "Random Int", insertText: "randInt()" },
  { name: "randDouble", detail: "Random Double", insertText: "randDouble()" },
  { name: "randRange", detail: "Random number in range", insertText: "randRange($0)" },
  { name: "setPrecision", detail: "Set decimal precision for print", insertText: "setPrecision($0)" },
  { name: "sizeof", detail: "Get size in bytes", insertText: "sizeof($0)" },
  { name: "sleep", detail: "Pause execution (ms)", insertText: "sleep($0)" },
  { name: "sronCmd", detail: "Execute SRON internal command", insertText: "sronCmd($0)" },
  { name: "sysCmd", detail: "Execute system command", insertText: "sysCmd($0)" },
  { name: "throwException", detail: "Throw a runtime exception", insertText: "throwException($0)" },
  { name: "typeof", detail: "Get type of value", insertText: "typeof($0)" },
  { name: "version", detail: "Get SRON version", insertText: "version()" },
];

// ─── Attribute Snippets ───
const ATTRIBUTE_SNIPPETS = [
  { label: "name", detail: "Function name attribute", insertText: "name : ${1:Main}" },
  { label: "args", detail: "Function arguments attribute", insertText: "args : (${1:Any val})" },
  { label: "type", detail: "Return type attribute", insertText: "type : ${1:Int}" },
  { label: "return", detail: "Return value attribute", insertText: "return : ${1:value}" },
  { label: "console", detail: "Print to console", insertText: "console : (${1:value})" },
  { label: "condition", detail: "Condition attribute", insertText: "condition : ${1:true}" },
  { label: "range", detail: "For-loop range attribute", insertText: "range : (${1:Int i = 0}, ${2:10})" },
  { label: "on", detail: "Foreach on attribute", insertText: "on : (${1:Any val}, ${2:list})" },
  {
    label: "if block", detail: "If statement block",
    insertText: "if : {\n\tcondition : ${1:true}\n\t$0\n}"
  },
  {
    label: "elif block", detail: "Elif statement block",
    insertText: "elif : {\n\tcondition : ${1:true}\n\t$0\n}"
  },
  {
    label: "else block", detail: "Else statement block",
    insertText: "else : {\n\t$0\n}"
  },
  {
    label: "for block", detail: "For loop block",
    insertText: "for : {\n\trange : (${1:Int i = 0}, ${2:10})\n\t$0\n}"
  },
  {
    label: "while block", detail: "While loop block",
    insertText: "while : {\n\tcondition : ${1:true}\n\t$0\n}"
  },
  {
    label: "foreach block", detail: "Foreach loop block",
    insertText: "foreach : {\n\ton : (${1:Any val}, ${2:list})\n\t$0\n}"
  },
  {
    label: "function", detail: "New SRON function",
    insertText: "{\n\tname : ${1:functionName}\n\t$0\n}"
  },
  {
    label: "main", detail: "Main function",
    insertText: "{\n\tname : Main\n\t$0\n}"
  },
  {
    label: "rotate", detail: "Rotate/swap values",
    insertText: "rotate : (${1:val1}, ${2:val2})"
  },
  {
    label: "windows block", detail: "Windows-only code block",
    insertText: "windows : {\n\t$0\n}"
  },
  {
    label: "linux block", detail: "Linux-only code block",
    insertText: "linux : {\n\t$0\n}"
  },
];

// ─── Variable Declaration Pattern ───
// Matches: Int x, Double val, String name, Any y, List lst, etc.
const VAR_DECL_REGEX = /\b(Any|Bool|Char|Double|FileReader|FileWriter|Int|List|LiteralString|String|Void)\s+([a-zA-Z_][a-zA-Z0-9_]*)\b/g;

/**
 * Scan the document for locally declared variables.
 * Returns a Map of variableName -> declared type.
 */
function extractLocalVariables(document) {
  const vars = new Map();
  const text = document.getText();
  let match;
  while ((match = VAR_DECL_REGEX.exec(text)) !== null) {
    const typeName = match[1];
    const varName = match[2];
    // Skip if it's a known keyword / constant / function to avoid noise
    if (!KEYWORDS.includes(varName) && !CONSTANTS.includes(varName)) {
      vars.set(varName, typeName);
    }
  }
  return vars;
}

// ─── Hover Lookup Maps (built once) ───
const KEYWORD_SET = new Set(KEYWORDS);
const CONSTANT_SET = new Set(CONSTANTS);
const TYPE_SET = new Set(TYPES);
const FUNCTION_MAP = new Map(FUNCTIONS.map(f => [f.name, f.detail]));
const SNIPPET_MAP = new Map(ATTRIBUTE_SNIPPETS.map(s => [s.label.split(" ")[0], s.detail]));

// ────────────────────────────────────────────────────────
//  ACTIVATION
// ────────────────────────────────────────────────────────

function activate(context) {

  // ─── 1. Completion Provider ───
  const completionProvider = vscode.languages.registerCompletionItemProvider(
    "sron",
    {
      provideCompletionItems(document) {
        const items = [];

        // Keywords
        for (const kw of KEYWORDS) {
          const item = new vscode.CompletionItem(kw, vscode.CompletionItemKind.Keyword);
          item.detail = "(keyword) SRON";
          items.push(item);
        }

        // Constants
        for (const c of CONSTANTS) {
          const item = new vscode.CompletionItem(c, vscode.CompletionItemKind.Constant);
          item.detail = "(constant) SRON";
          items.push(item);
        }

        // Types
        for (const t of TYPES) {
          const item = new vscode.CompletionItem(t, vscode.CompletionItemKind.TypeParameter);
          item.detail = "(datatype) SRON";
          items.push(item);
        }

        // Functions
        for (const fn of FUNCTIONS) {
          const item = new vscode.CompletionItem(fn.name, vscode.CompletionItemKind.Function);
          item.detail = "(function) " + fn.detail;
          item.insertText = new vscode.SnippetString(fn.insertText);
          items.push(item);
        }

        // Attribute Snippets
        for (const sn of ATTRIBUTE_SNIPPETS) {
          const item = new vscode.CompletionItem(sn.label, vscode.CompletionItemKind.Snippet);
          item.detail = "(snippet) " + sn.detail;
          item.insertText = new vscode.SnippetString(sn.insertText);
          items.push(item);
        }

        // Local variables from the current document
        const localVars = extractLocalVariables(document);
        for (const [varName, varType] of localVars) {
          const item = new vscode.CompletionItem(varName, vscode.CompletionItemKind.Variable);
          item.detail = "(variable) " + varType;
          items.push(item);
        }

        return items;
      }
    },
  );

  // ─── 2. Formatter Provider ───
  const formatterProvider = vscode.languages.registerDocumentFormattingEditProvider(
    "sron",
    {
      provideDocumentFormattingEdits(document) {
        const edits = [];
        const tabSize = vscode.workspace.getConfiguration("editor", document.uri).get("tabSize", 4);
        const insertSpaces = vscode.workspace.getConfiguration("editor", document.uri).get("insertSpaces", true);
        const indentChar = insertSpaces ? " ".repeat(tabSize) : "\t";

        let indentLevel = 0;
        const lines = [];

        for (let i = 0; i < document.lineCount; i++) {
          let raw = document.lineAt(i).text;
          let trimmed = raw.trim();

          // Skip empty lines – keep them as-is
          if (trimmed === "") {
            lines.push("");
            continue;
          }

          // Check if line is a comment starting with @
          const isComment = trimmed.startsWith("@");

          // Decrease indent before a closing brace
          if (trimmed.startsWith("}") && indentLevel > 0) {
            indentLevel--;
          }

          // Build the formatted line
          lines.push(indentChar.repeat(indentLevel) + trimmed);

          // Increase indent after opening brace (unless the line also closes)
          if (!isComment && trimmed.endsWith("{") && !trimmed.endsWith("}")) {
            indentLevel++;
          }
        }

        const fullRange = new vscode.Range(
          document.lineAt(0).range.start,
          document.lineAt(document.lineCount - 1).range.end
        );
        edits.push(vscode.TextEdit.replace(fullRange, lines.join("\n")));
        return edits;
      }
    }
  );

  // ─── 3. Run Command ───
  const runCommand = vscode.commands.registerCommand("sron.run", () => {
    const editor = vscode.window.activeTextEditor;
    if (!editor) {
      vscode.window.showErrorMessage("No active SRON file to run.");
      return;
    }

    const filePath = editor.document.fileName;
    if (!filePath.endsWith(".sron")) {
      vscode.window.showErrorMessage("The active file is not a .sron file.");
      return;
    }

    // Save the file before running
    editor.document.save().then(() => {
      const dir = require("path").dirname(filePath);
      const fileName = require("path").basename(filePath);

      // Reuse or create a terminal
      let terminal = vscode.window.terminals.find(t => t.name === "SRON");
      if (!terminal) {
        terminal = vscode.window.createTerminal({ name: "SRON", cwd: dir });
      }
      terminal.show(true);

      // First compile, then run
      terminal.sendText(`cd "${dir}" && sronc "${fileName}" && sron`);
    });
  });

  // ─── 4. Hover Provider ───
  const hoverProvider = vscode.languages.registerHoverProvider("sron", {
    provideHover(document, position) {
      const wordRange = document.getWordRangeAtPosition(position, /[a-zA-Z_][a-zA-Z0-9_]*/);
      if (!wordRange) return null;
      const word = document.getText(wordRange);

      const parts = [];

      // Check types first (highest priority label)
      if (TYPE_SET.has(word)) {
        parts.push(new vscode.MarkdownString(`**(datatype)** \`${word}\``));
      }

      // Check keywords
      if (KEYWORD_SET.has(word)) {
        parts.push(new vscode.MarkdownString(`**(keyword)** \`${word}\``));
      }

      // Check constants
      if (CONSTANT_SET.has(word)) {
        parts.push(new vscode.MarkdownString(`**(constant)** \`${word}\``));
      }

      // Check built-in functions
      if (FUNCTION_MAP.has(word)) {
        const desc = FUNCTION_MAP.get(word);
        parts.push(new vscode.MarkdownString(`**(function)** \`${word}()\` — ${desc}`));
      }

      // Check attribute snippets
      if (SNIPPET_MAP.has(word) && parts.length === 0) {
        const desc = SNIPPET_MAP.get(word);
        parts.push(new vscode.MarkdownString(`**(attribute)** \`${word}\` — ${desc}`));
      }

      // Check local variables
      if (parts.length === 0) {
        const localVars = extractLocalVariables(document);
        if (localVars.has(word)) {
          const varType = localVars.get(word);
          parts.push(new vscode.MarkdownString(`**(variable)** \`${varType} ${word}\``));
        }
      }

      if (parts.length > 0) {
        return new vscode.Hover(parts, wordRange);
      }
      return null;
    }
  });

  context.subscriptions.push(completionProvider, formatterProvider, runCommand, hoverProvider);
}

function deactivate() {}

module.exports = { activate, deactivate };
