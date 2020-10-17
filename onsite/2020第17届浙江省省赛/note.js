const repo_url = 'https://raw.githubusercontent.com/TI1050-HZNU/TI1050-Code-Repo/master/onsite/2020%E7%AC%AC17%E5%B1%8A%E6%B5%99%E6%B1%9F%E7%9C%81%E7%9C%81%E8%B5%9B/';
const practice_link = "";
const problem_id = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'];
const ac_status = [1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0];
const problem_code_path = ["a.cpp", "b.cpp", "c1.cpp", "d.cpp", "e.cpp", "f.cpp", "g.cpp", "h.cpp", "i.cpp", "j.cpp", "k.cpp", "l.cpp"];
const problem_code_suffix = ["cpp", "cpp", "cpp", "cpp", "cpp", "cpp", "cpp", "cpp", "cpp", "cpp", "cpp", "cpp"];
const problem_name = [
    "AD 2020", 
    "Bin Packing Problem", 
    "Crossword Validation",
    "Dividing the Points", 
    "Easy DP Problem", 
    "Finding a Sample", 
    "Gliding",
    "Huge Clouds",
    "Invoking the Magic",
    "Just an Old Problem",
    "Killing the Brute-forces",
    "List of Products"
];
const ac_author = [
    "Dup4 & Hsueh-",
    "all",
    "Dup4 & Hsueh-",
    "-",
    "all",
    "-",
    "Hsueh- & ltslts",
    "-",
    "Hsueh- & ltslts",
    "-",
    "Dup4",
    "-"
];
const ac_time = [
    "01:10(+)",
    "00:57(+)",
    "02:57(+1)",
    "",
    "02:09(+)",
    "",
    "03:33(+1)",
    "",
    "00:16(+)",
    "",
    "00:14(+)",
    ""
];

const template = 
`
<details class='note'><summary>目录</summary><div>

[TOC]

</div></details>

# Contest Info

[Practice Link](${practice_link})

${generate_table(ac_status, problem_id)}

- O    在比赛中通过
- Ø    赛后通过
- !    尝试了但是失败了
- \\-   没有尝试

# Solutions


`;

function get(url) {
    return new Promise((resolve, reject) => {
        $.get(url, function(data, err) {
            resolve(data);
        })
    })
}

function generate_table(ac_status, problem_id) {
    const len = ac_status.length;
    var str = [
        "|Solved|",
        "|:-:|",
        `|${ac_status.reduce((a, b) => a += b)}/${len}|`,
    ]
    for (let i = 0; i < len; ++i) {
        str[0] += problem_id[i] + "|";
        str[1] += ":-:|";
        str[2] += (ac_status[i] === 1 ? 'O' : '-') + "|";
    }
    return str.join("\n");
}

(async function () {
    let res = template;
    const len = problem_id.length;
    for (let i = 0; i < len; ++i) {
        const code = ac_status[i] === 1 ? await get([repo_url, problem_code_path[i]].join("")) : "";
        res += 
`
## Problem ${problem_id[i]}. ${problem_name[i]}

${ac_status[i] == 1 ? `Solved By ${ac_author[i]}. ${ac_time[i]}` : `Upsolved By ${ac_author[i]}.`}

### 题意


### 思路


<details class='info'><summary>代码</summary><div>

\`\`\`${problem_code_suffix[i]}
${code}
\`\`\`

</div></details>
`
    }
    console.log(res);
})();

