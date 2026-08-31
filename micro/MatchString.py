def MatchString(str_:str, match:str):
    match_indeces = []
    for i in range(len(str_)):
        if str_[i] == match[len(match_indeces)]: match_indeces.append(i)
        elif len(match_indeces) != 0 : match_indeces.clear()
        if len(match_indeces) == len(match) : break 
    return match_indeces

if __name__ == "__main__" :
    str_ = "JAKARTA EXPO"
    match = "AKAR"
    match_indeces = MatchString(str_, match)
    print(match_indeces)
    for i in match_indeces:
        print(str_[i], end="")
    print()
