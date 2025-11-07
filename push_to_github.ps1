<#
PowerShell helper to add, commit and push this repo to a remote GitHub repository.
Usage examples:
  # Default remote URL (your repo):
  .\push_to_github.ps1

  # Provide a different remote and branch:
  .\push_to_github.ps1 -RemoteUrl "git@github.com:your-username/your-repo.git" -Branch "main"

Notes:
- For HTTPS remote, you may need to use a Personal Access Token (PAT) or Git Credential Manager.
- For SSH remote (git@github.com:...), ensure your SSH key is added to your GitHub account.
- This script will initialize a git repo if one doesn't already exist.
- It commits all changes (git add -A); review before running if you need selective commits.
#>

param(
    [string]$RemoteUrl = "https://github.com/Naveenvaidani/Design-And-Analysis-Of-Algorithms.git",
    [string]$Branch = 'main',
    [string]$CommitMessage = "Add algorithm files and docs"
)

function ExitWithError($msg) {
    Write-Error $msg
    exit 1
}

# Check git
if (-not (Get-Command git -ErrorAction SilentlyContinue)) {
    ExitWithError "git is not installed or not in PATH. Install Git for Windows (https://git-scm.com/) and try again."
}

# Ensure script is run at repo root
$repoRoot = Get-Location
Write-Host "Repository root: $repoRoot"

# Initialize git if needed
if (-not (Test-Path .git)) {
    Write-Host "No git repository found. Initializing..."
    git init
} else {
    Write-Host "Existing git repository detected."
}

# Configure remote
$existing = git remote get-url origin 2>$null
if ($LASTEXITCODE -ne 0) {
    Write-Host "Adding remote origin -> $RemoteUrl"
    git remote add origin $RemoteUrl
} else {
    Write-Host "Updating remote origin -> $RemoteUrl"
    git remote set-url origin $RemoteUrl
}

# Stage all changes
Write-Host "Staging all changes..."
git add -A

# Exclude this helper script from being committed/pushed
if (Test-Path ".\push_to_github.ps1") {
    Write-Host "Excluding push_to_github.ps1 from commit/push..."
    # Ensure .gitignore contains the entry so future commits ignore it
    if (-not (Test-Path ".gitignore") -or -not (Select-String -Path .gitignore -Pattern 'push_to_github.ps1' -Quiet -SimpleMatch 2>$null)) {
        Add-Content -Path .gitignore -Value "push_to_github.ps1"
        git add .gitignore
    }
    # Unstage the helper script if it was staged
    git reset -- "push_to_github.ps1" 2>$null
}

# Commit
Write-Host "Committing..."
git commit -m "$CommitMessage" 2>$null
if ($LASTEXITCODE -ne 0) {
    Write-Host "Nothing to commit or commit failed (maybe no changes). Continuing to push if branch exists..."
}

# Push
Write-Host "Pushing to origin/$Branch..."
# If the branch doesn't exist remotely, -u will set the upstream
$pushCmd = "git push -u origin $Branch"
Invoke-Expression $pushCmd

if ($LASTEXITCODE -eq 0) {
    Write-Host "Push successful."
} else {
    Write-Host "Push failed. Check remote, authentication (SSH keys or PAT), and network."
}
