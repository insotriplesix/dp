"""
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
"""

import os
import gitlab
from docopt import docopt
from git import Repo


def process_project(project, root_dir, need_pull):
    git_url = project.http_url_to_repo
    project_dir = root_dir + project.path

    if not os.path.exists(project_dir):
        print("Cloning into '{}' ...".format(project.path))
        Repo.clone_from(
            git_url,
            project_dir,
            branch='master',
            depth=1,
            config='http.sslVerify=false'
        )
        print("Done.")
    elif need_pull:
        print("Pulling into '{}' ...".format(project.path))
        Repo(project_dir).remotes.origin.pull()
        print("Done.")
    else:
        print("Project '{}' already exists, skipped.".format(project.path))


def run():
    arguments = docopt(
        __doc__,
        help='True',
        version='GitLab Synchronizer v1.0\n  -> made by 5aboteur'
    )
    gl = gitlab.Gitlab(arguments['--url'], private_token=arguments['--token'])
    gl.auth()
    group = gl.groups.get(int(arguments['--gid']))
    root_dir = os.getcwd() + '/' + arguments['--root'] + '/'

    if not os.path.exists(root_dir):
        os.mkdir(root_dir)
    os.chdir(root_dir)

    print("Synchronize projects ...")
    for p in group.projects.list():
        process_project(p, root_dir, arguments['--pull'])
    print("All done!")


if __name__ == '__main__':
    run()
