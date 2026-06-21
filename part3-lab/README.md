# PART 3.A — Laboratory Deployment & Architecture Documentation

# 1. Infrastructure Architecture Table

| Container Name | Full Network Hostname | Base Interface | Segment / Logical Subnet | Technical Role / Purpose |
| --- | --- | --- | --- | --- |
| **p-web-01** | 'p-web-01.acme-infinity-servers.com' | 'br_public' | Public ('172.16.10.0/24') | Main Web Server (Flask/Python - Port 80) |
| **p-web-02** | 'p-web-02' | 'br_public' | Public ('172.16.10.0/24') | Secondary Public Web Server |
| **p-ftp-01** | 'p-ftp-01' | 'br_public' | Public ('172.16.10.0/24') | Public FTP File Repository |
| **p-jumpbox-01**| 'p-jumpbox-01' | 'br_public' | Public ('172.16.10.0/24') | Network Bastion / Jump Host |
| **c-db-01** | 'c-db-01' | 'br_corporate' | Corporate ('10.1.0.0/24') | Primary Relational Database |
| **c-db-02** | 'c-db-02' | 'br_corporate' | Corporate ('10.1.0.0/24') | Secondary MySQL Database (Port 3306) |
| **c-redis-01** | 'c-redis-01' | 'br_corporate' | Corporate ('10.1.0.0/24') | In-Memory Key-Value Cache (Port 6379) |
| **c-backup-01** | 'c-backup-01' | 'br_corporate' | Corporate ('10.1.0.0/24') | Internal Data Backup Server |


# 2. Isolated Dual-Network Topology Diagrams

Based on the virtual interfaces ('veth') and network bridges validated on the Ubuntu host engine, the environment is strictly split into two independent Docker-managed segments:

# DIAGRAM A: Public Network Segment

  [ Ubuntu Host Interface: br_public ] ─── IP: 172.16.10.1 (Gateway)
                 │
                 ├── (veth) ─── [ p-web-01 ] ─── IP: 172.16.10.10
                 ├── (veth) ─── [ p-web-02 ] ─── IP: 172.16.10.20
                 ├── (veth) ─── [ p-ftp-01 ] ─── IP: 172.16.10.30
                 └── (veth) ─── [ p-jumpbox-01 ] ── IP: 172.16.10.40

# DIAGRAM B: Corporate Network Segment
[ Ubuntu Host Interface: br_corporate ] ─── IP: 10.1.0.1 (Gateway)
                 │
                 ├── (veth) ─── [ c-db-01 ] ──── IP: 10.1.0.30
                 ├── (veth) ─── [ c-db-02 ] ──── IP: 10.1.0.35
                 ├── (veth) ─── [ c-redis-01 ] ── IP: 10.1.0.40
                 └── (veth) ─── [ c-backup-01 ] ─ IP: 10.1.0.50

### 4. Interactive Container Access Verification (`docker exec`)

To validate local infrastructure access, communication hooks, and privilege boundaries, a live terminal session was initiated on the primary web instance (`p-web-01`).

# Executing interactive terminal routing to p-web-01
andres@andres-VirtualBox:~/Black-Hat-Bash/lab$ sudo docker exec -it p-web-01 bash

# Auditing user context assignment (Expected: root lifecycle)
root@p-web-01:/app# whoami
root

# Validating Internal FQDN resolution within the network bridge
root@p-web-01:/app# hostname
p-web-01.acme-infinity-servers.com

# Inspecting internal runtime directory mapping and application structures
root@p-web-01:/app# ls -la
total 40
drwxr-xr-x 1 root root 4096 Jun 20 17:54 .
drwxr-xr-x 1 root root 4096 Jun 20 17:54 ..
drwxr-xr-x 2 root root 4096 Jun 20 17:54 __pycache__
-rw-rw-r-- 1 root root 1832 Jun 20 17:33 app.py
drwxr-xr-x 1 root root 4096 Jun 20 17:52 files
-rw-rw-r-- 1 root root 7177 Jun 20 17:33 index.html
drwxr-xr-x 2 root root 4096 Jun 20 17:33 static
-rw-rw-r-- 1 root root  433 Jun 20 17:33 upload.html
drwxr-xr-x 2 root root 4096 Jun 20 17:52 uploads

# Severing session link and returning to Ubuntu host environment
root@p-web-01:/app# exit
exit