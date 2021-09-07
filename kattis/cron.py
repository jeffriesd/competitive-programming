# problem: https://nadc21.kattis.com/problems/simplecronspec

n = int(input())


def make_minute():
    minute = {}
    for s in range(0, 60):
        minute[s] = 0
    return minute
    
def make_hour():
    hour = {}
    for m in range(0,60):
        hour[m] = make_minute()
    return hour

def make_day():
    day = {}
    for h in range(0,24):
        day[h] = make_hour()
    return day

def parse_value_or_range(string):
    if "-" in string:
        lower, upper = string.split("-")
        return int(lower), int(upper)
    return int(string), int(string)


# return list of tuples 
def parse_range(string):
    ranges = string.split(",")
    ans = []
    for r in ranges:
        lo, hi = parse_value_or_range(r)
        ans.append((lo, hi))
    return ans

# use inclusive ranges 
def get_ranges(secs, lo, hi ):
    if secs == "*":
        return [(lo, hi)]
    if ("-" in secs) or ("," in secs):
        return parse_range(secs)
    else:
        sec_value = int(secs)
        return [(sec_value, sec_value)]


schedule = make_day()



for _ in range(n):
    line = input()
    hrs, mins, secs = line.split()

    sec_ranges = []
    min_ranges = []
    hr_ranges = []

    sec_ranges = get_ranges(secs, 0, 59)
    min_ranges = get_ranges(mins, 0, 59)
    hrs_ranges = get_ranges(hrs,  0, 23)

    for (hlo, hhi) in hrs_ranges:
        for hr in range(hlo, hhi+1):
            for (mlo, mhi) in min_ranges:
                for mn in range(mlo, mhi+1):
                    for (slo, shi) in sec_ranges:
                        for ss in range(slo, shi+1):
                            schedule[hr][mn][ss] += 1
    # print(sec_ranges)
    # print(min_ranges)
    # print(hrs_ranges)
    # print("----")




at_least_one = 0
job_starts = 0
# count number of job starts
for hr in schedule:
    for mn in schedule[hr]:
        for ss in schedule[hr][mn]:
            if schedule[hr][mn][ss] > 0:
                at_least_one += 1
                job_starts += schedule[hr][mn][ss]


print(at_least_one,job_starts)



  
