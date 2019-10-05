# GitLab Synchronizer

The utility that synchronize all of your remote projects with local storage.

## Launch steps

1. Python >= `3.6.8`

2. Install the `pip` manager and run the command:
`$ pip install -r requirements.txt`

3. Create your personal [token](https://docs.gitlab.com/ee/user/profile/personal_access_tokens.html) to access the API

4. Run the script by following the next rules (more about syntax [here](http://docopt.org/)):

```none
Usage:
    synchronizer.py (-t <TOKEN>) (-g <GID>) [-p] (-r <ROOT>) [-u <URL>]
    synchronizer.py -h
    synchronizer.py -v

Options:
    -g, --gid=<GID>      - group ID
    -h, --help           - help screen
    -p, --pull           - pull repository
    -r, --root=<ROOT>    - root directory
    -t, --token=<TOKEN>  - GitLab token
    -u, --url=<URL>      - GitLab URL [default: https://gitlab.com/]
    -v, --version        - program version
```
