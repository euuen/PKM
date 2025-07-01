MathJax = {
    tex: {
        inlineMath: [['$', '$'], ['\\(', '\\)']], // 行内公式分隔符
        displayMath: [['$$', '$$'], ['\\[', '\\]']], // 块级公式分隔符
    },
    options: {
        ignoreHtmlClass: 'no-math', // 忽略包含此类的元素
        processHtmlClass: 'mathjax' // 强制处理包含此类的元素
    }
};