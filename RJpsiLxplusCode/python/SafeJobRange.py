def SafeJobRange(lower, upper):
    from Ganga.Core.GangaRepository import RegistryKeyError

    list = []
    for i in range(lower,upper):
        try:
            jobs(i)
            list.append(i)
        except RegistryKeyError:
            continue
    return list

