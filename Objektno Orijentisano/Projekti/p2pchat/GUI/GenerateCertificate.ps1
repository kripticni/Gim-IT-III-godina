$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition

$cert = New-SelfSignedCertificate `
    -DnsName "P2PChatCert" `
    -CertStoreLocation "cert:\CurrentUser\My" `
    -KeyExportPolicy Exportable `
    -FriendlyName "P2PChatCert" `
    -NotAfter (Get-Date).AddYears(100)

$password = ConvertTo-SecureString -String "PeerToPeerChatCertificate" -Force -AsPlainText

$pfxPath = Join-Path $scriptDir "P2PChatCert.pfx"
Export-PfxCertificate -Cert $cert -FilePath $pfxPath -Password $password

Write-Host "Certifikat eksporotovan na: $pfxPath"