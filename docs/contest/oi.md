author: Ir1d, Planet6174, abc1763613206, StudyingFather, cjsoft, Marcythm, luoguyuntianming, ChungZH, Xeonacid, YZircon, i-Yirannn, H-J-Granger, NachtgeistW, YuzhenQin, Andycode3759, HHH2309, shigengxin123456, Re-Ori, hcx1204

## Introduction

**Olympiad in Informatics** (OI) is a subject competition widely held among secondary-school students, similar in nature to competitions in physics, mathematics, and other subjects. OI examines contestants' ability to use algorithms, data structures, and mathematical knowledge to solve practical problems by writing computer programs.

There are many kinds of OI competitions. In China alone, they include:

-   National Olympiad in Informatics in Provinces (NOIP)
-   National Olympiad in Informatics (NOI)
-   National Olympiad in Informatics Winter Camp (WC)
-   China Team Selection Competition for the International Olympiad in Informatics (CTSC)

International OI competitions include:

-   International Olympiad in Informatics (IOI)
-   USA Computing Olympiad (USACO)
-   Japanese Olympiad in Informatics (JOI)
-   Asia-Pacific Informatics Olympiad (APIO)

    ......

For most contestants, each new season begins with the CSP-J/S first round in September.

In China, the only language currently allowed in OI competitions is C++ (C and Pascal were once allowed, but support for both has been discontinued). Different competitions have different requirements for the C++ version. Problems are generally related to algorithms or data structures. Problem formats include traditional problems (the most common type, with prescribed input from and output to files) and non-traditional problems (output-only problems, interactive problems, code-completion problems, and so on).

## Contest Formats

### OI Format

Contestants have only one submission opportunity. Judging results are not visible during the contest, and scores are announced after the contest. Each problem has multiple test points; contestants receive the corresponding score according to the number of test points passed for each problem. Each test point may also have partial scores, so points can still be awarded even if only part of the data is passed.

???+ note "selfEval self-judging tool"
    Nowadays, some NOI-series contests provide the selfEval self-judging tool. selfEval is built into the customized national-contest version of NOI Linux. Since its official announcement and adoption at NOI2023, selfEval has gradually been used in subsequent NOI national contests, APIO (China region), NOI Winter Camp, and other events. Contestants can use selfEval to test their programs on a set of test data (called pretest data) and receive feedback. The number of self-tests in each contest has a specified upper limit (50 self-tests at NOI2024 and 30 self-tests at NOI2025), and the pretest data is also invisible to contestants. Because the pretest data differs from the official test data, self-test results are only for debugging and cannot be treated as official judging results. When a contestant pretests the same problem multiple times, the pretest data used is the same.

CSP-J/S second round, NOIP, provincial selection, and NOI all use the OI format.

### IOI Format

Contestants have multiple submission opportunities during the contest. Submissions are judged in real time and results are returned. There is no penalty for an incorrect submission. Each problem has multiple test points, and contestants receive the corresponding score according to the number of test points passed for each problem.

APIO and IOI both use the IOI format. Domestic contests are also gradually moving closer to the IOI format.

### Codeforces (CF) Format

[Codeforces](https://codeforces.com) is an online judge system that regularly holds contests.

Its contests are characterized by testing only part of the data (Pretests) during the contest, then returning the full results for all test points after the contest ends (System Tests). Contestants may submit multiple times during the contest and may Hack other contestants' code (here Hack means submitting a test case that makes another contestant's code fail to produce the correct answer). To Hack, contestants must lock their own code (in other words, they cannot resubmit that problem during the contest). During Hacks, contestants' programs cannot be copied locally for testing; the source code is converted into an image.

Codeforces also provides another format called Extended ICPC (Extended ICPC or ICPC+). In this format, all data is tested during the contest, but after the contest ends there is a 12-hour site-wide Hack period. During Hacks, contestants' programs may be copied locally for testing.

## Major Competitions

### CSP-J/S

**CSP-J/S** (English: Certified Software Professional Junior/Senior) is a non-professional software capability certification test established by CCF after NOIP was canceled in 2019. Before 2025 it was open to all ages, and [was later changed to age 12 and above](https://www.noi.cn/xw/2025-02-13/837984.shtml).

CSP-J/S is divided into the Junior level (abbreviated CSP-J) and Senior level (abbreviated CSP-S). The schedule is divided into two rounds: the first round (usually in September each year) and the second round (usually in October each year). The first round is a written test that examines computer theory, common operational knowledge, and basic algorithmic and mathematical knowledge. The second round is a computer-based exam; both the Junior and Senior groups have 4 problems. The Junior group has 3.5 hours, and the Senior group has 4 hours (except CSP-S 2019, which used the old NOIP Senior-group format, with the contest split into two days, 3 problems and 3.5 hours per day). The first round is open for registration to all students in society aged 12 and above. After ranking-based screening, contestants with excellent results have the opportunity to participate in the second round.

Fees must be paid to CCF for registration in the first/second round and for problem appeals after the second round.

Both rounds certify contestants' results by province according to rankings, divided into first, second, and third classes.

### NOIP

**NOIP** (English: National Olympiad in Informatics in Provinces; Chinese: National Youth Informatics Olympiad League) is an informatics competition organized by the People's Republic of China for secondary-school students in China (including Hong Kong and Macao).

Old format in and before 2018: NOIP was divided by participant level into the Popularization group and Senior group, with an Entry group piloted in Shanghai in 2018; by stage, it was divided into the preliminary round and the final round. The preliminary round tested some basic computer knowledge and algorithm fundamentals, while the final round was a computer-based exam. It was usually held on the second weekend of November: Senior group first session on Saturday morning 8:30-12:00 (3.5 hours, 3 problems), Popularization group on Saturday afternoon 14:30-18:00 (3.5 hours, 4 problems), and Senior group second session on Sunday morning 8:30-12:00 (3.5 hours, 3 problems). The same set of papers was used nationwide, but award rules were uniformly specified by CCF (China Computer Federation) according to each province's circumstances and announced after the contest on the [NOI official website](http://www.noi.cn). The first-prize cutoff scores varied slightly by province.

NOIP was [suspended by CCF](http://www.noi.cn/xw/2019-08-16/715365.shtml) on August 16, 2019, and [announced to be resumed](http://www.noi.cn/xw/2020-01-21/715520.shtml) on January 21, 2020. The NOIP format since 2020 differs from the previous format as follows:

-   The preliminary round was canceled and replaced by the CSP-J/S first round;
-   The Popularization group was canceled and replaced by CSP-J. Since then, NOIP has had only one group, aimed at contestants at Senior-group level;
-   The schedule was reduced from the previous two days with 6 problems and 3.5 hours per day to one day with 4 problems and 4.5 hours in total.
-   Contestants must achieve a certain ranking in the CSP-S second round to qualify for NOIP; the specific quotas vary by province. Provincial qualification quotas for NOIP are related to that province's number of participants and results in the previous season.

No additional fee is required to register for NOIP or to file problem appeals.

NOIP ranks and awards prizes by province. As of 2019, contestants who won a provincial first prize in the Senior group could obtain independent-admission qualifications at most universities.

> In January 2020, the Ministry of Education of the People's Republic of China issued the [Opinions on Piloting Reform of Enrollment for Basic Disciplines in Some Universities](http://www.moe.gov.cn/srcsite/A15/moe_776/s3258/202001/t20200115_415589.html). The opinions state that, starting in 2020, independent university admissions would no longer be organized, and pilot reforms for enrollment in basic disciplines (the Strong Foundation Plan) would be carried out at some first-class university construction institutions.

### Provincial Team Selection

**Provincial team selection** (abbreviated provincial selection) is used to select each province's representative team for the national contest, and is generally held from January to April each year. The schedule is generally divided into two days, with 3 problems and 4.5 hours each day.

Provincial-selection problems are decided by each province independently. The current trend is that many provinces choose joint problem setting.

The quotas for each provincial team have complicated calculation formulas and are generally related to previous results and number of participants. Usually, the NOIP score must account for a certain proportion of the provincial-selection criteria. According to the rules, junior-high-school contestants can only be selected as class E contestants and cannot participate in class A or B selection. There are 5 class A contestants ([at least 1 female](https://www.noi.cn/xw/2024-08-26/829152.shtml)); other contestants enter team B in order according to the given quotas and their scores. The number of contestants from one school participating in NOI cannot exceed one third (rounded) of the total number of class A and B quotas in the province. The highest-scoring female contestant selected for team A does not count toward this ratio (called the 1/3 restriction or 1/3 elimination; see the [official CCF explanation](https://www.noi.cn/xw/2022-12-14/781364.shtml) for details).

Since 2020, NOI provincial team selection has used unified problem setting and judging by CCF. Provinces capable of setting problems may do so independently, but the selection method must be approved by CCF. Since 2024, NOI provincial team selection has returned to independent problem setting by each province. Provinces with such needs may organize joint exams or use other provinces' problems, but the specific plan must be approved by CCF.

### NOI

**NOI** (English: National Olympiad in Informatics; Chinese: National Informatics Olympiad) is the highest-level contest for provincial representative teams in China, including Hong Kong and Macao.

NOI is usually held in July, and contestants are divided into official contestants and summer-camp contestants. Official contestants are further divided into three classes: classes A and B are official provincial-team contestants, while class C contestants are invitational-contest contestants. Classes A and B correspond to the provincial team's class A and B contestants (class A receives a 5-point bonus when scores are calculated); class C is nominally a reward quota for schools that have made outstanding contributions to CCF. Summer-camp contestants are divided into classes D and E, corresponding respectively to high-school and junior-high-school contestants participating as unofficial contestants. If summer-camp contestants exceed the score cutoff, they receive only a score certificate and no medal (the value of the same score is somewhat lower). The top 50 official contestants form the national training team and obtain recommendation-based admission qualifications.

On international platforms, to distinguish it from other competitions also called NOI, it is sometimes called CNOI.

### CTT

**CTT** (English: China Team Training; Chinese: International Olympiad in Informatics National Training Team Training) is a training and selection activity held every winter for IOI national training team contestants, consisting of 3-4 tests. In addition to national training team members, some contestants who achieved excellent results in that year's NOI may also participate in CTT under the name "elite training".

CTT, together with regular assignments and other processes, forms the first stage of national-team selection. Since 2021, the top 30 contestants in the first stage have become national candidates and entered the second stage of selection (WC).

### WC

**WC** (English: Winter Camp; Chinese: National Youth Informatics Olympiad Winter Camp) is an activity held every winter at the location where that year's NOI was held. Although the activity is mainly used for training-team instruction and national-team selection, contestants who achieved good results in the previous year's NOIP and CSP-S second round may also participate as unofficial campers.

WC consists of several days of training and tests. Test results are combined with results from previous stages to calculate the comprehensive ranking of training-team contestants. Before 2020, there was only one test, and training-team contestants and unofficial campers had the same test problems. The top 15 training-team contestants by comprehensive score became national candidates and participated in the final stage of selection (CTS, etc.). Since 2021, as CTS's national-team selection function was incorporated into WC, national candidates' testing changed to two tests, while unofficial campers still take one test, and the unofficial campers' problems partially overlap with the candidate-team test problems. The top 6 candidates by comprehensive ranking enter the final interview, after which 4 official contestants and 2 reserve contestants are selected to participate in that year's IOI.

### APIO

**APIO** (English: Asia-Pacific Informatics Olympiad; Chinese: Asia-Pacific Informatics Olympiad) is an informatics subject competition for school students in the Asia-Pacific region. CCF holds a mirror contest for the China region in early May each year. Training activities are held around the contest day.

APIO contestants can be divided into class A and class B. The top six class A contestants (including ties) may participate in the evaluation of APIO international awards, while class B contestants can only participate in awards for the China region.

### CTS

**CTS** (formerly CTSC, English: China Team Selection Competition; Chinese: China Team Selection Competition for the International Olympiad in Informatics) is used to select the national team (6 people) from the national candidates (15 people) to prepare for that summer's IOI, including 4 official contestants and 2 reserve contestants. As with WC, contestants who achieved good results in the previous year's NOIP may also participate (but not in selection).

APIO and CTS both register by province, generally determining participants for APIO and CTS according to NOIP scores (the two events are usually very close in time).

CTS in 2020 was canceled due to the pandemic, and that year's national training team was selected through NOI. Since 2021, the CTS selection process has been replaced by WC.

### IOI

**IOI** (English: International Olympiad in Informatics; Chinese: International Olympiad in Informatics) is an annual informatics subject competition for secondary-school students worldwide. Each country has four participants, and the contest is generally livestreamed. In the IOI format, each problem has Subtasks, and each subtask corresponds to a certain score.

### Subject Camps

#### Peking University (PKU)

-   Peking University Informatics Winter Experience Camp (PKUWC): held around the Winter Camp.
-   Peking University Informatics Experience Camp (PKUSC): generally held on campus in June. Because the contest is held in the school's computer labs, the computer-lab environment is Windows and the contest system is OpenJudge.
-   Peking University Summer Class for Secondary-School Students (Informatics): held during the summer vacation, for science-track students in grade 11.

#### Tsinghua University (THU)

-   Department of Computer Science "university-secondary transition" winter seminar and teaching activity: equivalent to an informatics winter camp, sometimes abbreviated in English as THUWC. It generally lasts two days, with contests in the morning (the first day is a standard OI contest, and the second day is Tsinghua's original "engineering problem" contest) and course training in the afternoon.

## OI Competitions in Other Countries and Regions

### United States: USACO

Official website: <http://www.usaco.org/>

USACO may be the foreign OI competition most familiar to domestic contestants (and possibly also the foreign OI competition with the most Chinese editorials).

Every year from winter to early spring, USACO holds one online contest each month. A contest lasts 3\~5 hours.

According to the official website, USACO contests are divided into these 4 difficulty divisions (3 divisions before the 2015\~2016 school year):

-   Bronze division, suitable for programming beginners, especially students who have learned only the most basic algorithms (such as sorting and binary search);
-   Silver division, suitable for students starting to learn basic algorithmic techniques (such as recursion, search, and greedy algorithms) and basic data structures;
-   Gold division, where students encounter more complex algorithms (such as shortest paths and DP) and more advanced data structures;
-   Platinum division, suitable for contestants with solid algorithm-design ability. The Platinum division helps them challenge themselves with complex and more open-ended problems.

In China, the OJ platform with the most complete collection of USACO problems is currently Luogu.

### Poland: POI

Official website: <https://oi.edu.pl/>

Official submission site: <https://szkopul.edu.pl/p/default/problemset/>

POI is one of the foreign OI competitions most commonly practiced by many provincial-selection contestants.

According to the description on the [POI official website](https://oi.edu.pl/l/42/), POI proceeds as follows:

-   First round: six problems (five problems up to and including the 31st edition), online contest;
-   Second round: includes one practice contest and two official contests, with one problem in the practice contest and two problems in each official contest;
-   Third round: includes one practice contest and two official contests, with one problem in the practice contest and three problems in each official contest.

In some years, a contest named ONTAK was held. Its official name was POI Training Camp, corresponding to China's national training team training contests (CTT).

In addition, Poland also holds a domestic open contest called PA, roughly meaning "algorithmic battles". Its official website is: <https://potyczki.mimuw.edu.pl/>.

Currently, among domestic OJs, BZOJ has the most complete collection of POI problems.

### Croatia: COCI

Official website (English): <http://www.hsin.hr/coci/>

Official website (Croatian): <http://www.hsin.hr/honi/>

A contest with a very wide difficulty range, roughly from Popularization - to provincial selection -.

In the past, all COCI problems provided statements, data, editorials, and standard solutions. From the end of 2017, COCI editorials and standard solutions stopped being updated. In the 2019-2020 season, editorials and standard solutions started being updated again.

Luogu, BZOJ, and LibreOJ all have a small number of COCI problems.

### Japan: JOI

Official website: <https://www.ioi-jp.org/>

JOI (Japanese: 日本情報オリンピック; Chinese: Japanese Informatics Olympiad) provides statements, data, editorials, and standard solutions for all problems. The JOI finals and spring camps in recent years have provided English statements, but not English editorials. JOI Open problems over the years have all provided English statements and editorials.

JOI proceeds as follows:

-   Preliminary round (予選)
-   Final round (本選/JOI Final)
-   Spring camp (春季トレーニング合宿/JOI Spring Camp/JOISC)
-   Open contest (通信教育/JOI Open Contest)

The preliminary round is relatively easy. Since the 2019/2020 season, the preliminary round has been divided into multiple rounds. JOI Final difficulty is roughly from Senior - to Senior +. The difficulty of JOISC and JOI Open problems ranges from Senior to NOI -.

Most JOI problems can be submitted on [AtCoder](https://atcoder.jp/). You can find more JOI problems (Japanese statements) on the JOI official website or AtCoder.

Currently, LibreOJ and BZOJ have problems from recent JOI Finals, JOISCs, and JOI Opens.

### Russia: ROI

Official website: <http://neerc.ifmo.ru/school/archive/index.html>

Online submission site: <https://contest.yandex.ru/roiarchive/> and Codeforces (some problems).

ROI (Russian: олимпиадная информатика; Chinese: Russian Informatics Olympiad) is Russia's informatics competition.

Process:

-   Municipal Stage (Муниципальный этап)
-   Regional Stage (Региональный этап)
-   Final Stage (Заключительный этап)

Currently, LibreOJ has translations of ROI final-round problems from recent years.

In addition, Russia has the following larger competitions for secondary-school students:

-   Online Informatics Olympiads (Russian: Интернет-олимпиады по информатике)
    -   Official website: <http://neerc.ifmo.ru/school/io/index.html>
    -   This competition is organized by ROI problem setters.
-   All-Russian Team Informatics Competition for School Students (Russian: Всероссийской командной олимпиады школьников)
    -   Official website: <http://neerc.ifmo.ru/school/russia-team/index.html>
    -   The preliminary contest for this competition, Moscow Team Olympiad, can be submitted on Codeforces.
-   Innopolis Open
    -   Official website <https://olymp.innopolis.ru/en/ooui/information/>
-   Open Programming Olympiad for School Students (Открытая олимпиада школьников по программированию)
    -   Official website: <https://olympiads.ru/zaoch/>
    -   The official website says this competition corresponds to ROI.

### Canada: CCC & CCO

CCC (English: Canadian Computing Competition) and CCO (English: Canadian Computing Olympiad) have information and problems from past years available on their [official website](https://cemc.math.uwaterloo.ca/contests/past_contests.html#ccc).

[CCC](https://dmoj.ca/problems/?category=4) and [CCO](https://dmoj.ca/problems/?category=24) can be submitted on DMOJ, which also has CCC editorials.

CCC Junior/Senior is close to NOIP Popularization/Senior-group difficulty. Winning a gold medal in CCO may require roughly NOI silver-medal level.

### Singapore: NOI SG

Official website: <https://noisg.comp.nus.edu.sg/noi/>

Its full name is Singapore National Olympiad in Informatics, and in Singapore's domestic context it is also called NOI when this does not cause ambiguity. Its format is divided into an Online Qualification Contest and a Final Contest. Schools register for the Online Qualification Contest as units; contestants participate at their own schools and submit remotely over the Internet. Qualification-contest results are ranked only within each school, and the top 5 contestants with nonzero scores are eligible to represent the school in the national final.

Currently, domestic OJs have relatively sparse coverage of NOI SG problems. Past statements, test data, and official standard programs can be found on the [official GitHub account](https://github.com/noisg).

### Taiwan Region: Informatics Olympiad

The Taiwan region uses a Traditional Chinese term for informatics in OI, rather than the term commonly used in mainland China.

Contestants from the Taiwan region who want to participate in IOI need to go through these rounds:

-   Regional Informatics Subject Ability Competition (區域資訊學科能力競賽)
-   National Informatics Subject Ability Competition (全國資訊學科能力競賽)
-   Informatics Study Camp (資訊研習營/TOI)

### Other Countries

-   Australia: AIO: <https://orac.amt.edu.au/hub/aio/>

    -   Difficulty is similar to NOI.

-   United Kingdom: British Informatics Olympiad: <https://www.olympiad.org.uk/>

    -   Difficulty is too low.

-   Czech Republic: Matematická olympiáda–kategorie P: <http://mo.mff.cuni.cz/p/archiv.html>

-   Romania: Olimpiada Nationala de Informatica: <http://olimpiada.info/>
    -   Look for statements, test data, and editorials in tabs containing the word Subiecte.

## Other International OI Competitions

### BalticOI

**BalticOI** is aimed at countries around the Baltic Sea. Participating countries in BalticOI 2018 included Lithuania, Poland, Estonia, Finland, and 9 countries in total. The problems are difficult.

Except in 2017, BalticOI publishes statements, test data, and editorials every year. BalticOI does not have a fixed official website; each year's host creates a new website. See the [post](https://loj.ac/article/416) for official websites from past years.

Currently, LibreOJ has BalticOI problems from nearly the past ten years.

### BalkanOI

**BalkanOI** is aimed at countries around the Balkan region. Participating countries in BalkanOI 2018 included Romania, Greece, Bulgaria, Serbia, and 12 countries in total. The problems are difficult.

BalkanOI publishes statements, test data, and editorials only in some years. See the [post](https://loj.ac/article/416) for official websites.

### CEOI

The participating countries in CEOI 2018 partially overlapped with the two contests above, including Poland, Romania, Georgia, Croatia, and others. The problems are difficult.

CEOI publishes statements, test data, and editorials every year. See the [post](https://loj.ac/article/416) for official websites.

### eJOI

**eJOI** stands for European Junior Olympiad in Informatics. Participating countries include Russia, Armenia, Bulgaria, Poland, and others. The problems are relatively difficult.

eJOI publishes statements, test data, and editorials every year. See the [post](https://loj.ac/article/416) for official websites.

### NOI

???+ warning "Warning"
    This is not the "National Olympiad in Informatics".

**NOI** stands for Nordic Olympiads in Informatics.

Official website: <http://nordic.progolymp.se>

This competition only started in the last two years and is aimed at Nordic countries.

## References

-   [ICPC/CCPC Contests and Formats](./icpc.md)
-   ["Translation Group" Addresses of Some Continental-Level OI Competitions](https://loj.ac/article/416)
