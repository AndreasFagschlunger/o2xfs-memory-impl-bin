plugins {
    `cpp-library`
    `maven-publish`
    `visual-studio`
}

import org.gradle.language.cpp.internal.DefaultCppBinary

group = "at.o2xfs"
version = "1.0-SNAPSHOT"

val javaHome = System.getenv("JAVA_HOME") ?: System.getProperty("java.home")

val javah by tasks.registering(Exec::class) {
    val javah = (System.getenv("JAVA_HOME") ?: System.getProperty("java.home")) + "/bin/javah.exe"
    commandLine(javah, "-d", file("src/main/public"), "-cp", file("../o2xfs-memory-impl/src/main/java"), "at.o2xfs.memory.impl.win32.Win32MemorySystem")
}

library {
    targetMachines.add(machines.windows.x86)
    targetMachines.add(machines.windows.x86_64)
}

val libIncludePath = files("$javaHome/include", "$javaHome/include/win32")

val mainLib: ProductionCppComponent = components.find{ it.name == "main" } as ProductionCppComponent
mainLib.binaries.whenElementFinalized({
    val binary = this as DefaultCppBinary;
    project.dependencies {
        if(binary.isOptimized) {
            add(binary.includePathConfiguration.name, libIncludePath)
        } else {
            add(binary.includePathConfiguration.name, libIncludePath)
        }
    }
})

tasks.register<Jar>("dist") {
    dependsOn("assembleReleaseX86", "assembleReleaseX86-64")
    archiveFileName.set("o2xfs-memory-impl-bin.jar")
    destinationDirectory.set(file("$buildDir/dist"))
    from("$buildDir/lib/main/release/x86/o2xfs-memory-impl-bin.dll") {
        into("x86")
    }
    from("$buildDir/lib/main/release/x86-64/o2xfs-memory-impl-bin.dll") {
        into("x86_64")
    }
    rename("(.+)-bin(.+)", "$1$2")
}

tasks.withType<PublishToMavenLocal>().configureEach {
    onlyIf {
        publication == publishing.publications["mavenJava"]        
    }
}

publishing {
    publications {
        create<MavenPublication>("mavenJava") {
            artifact(tasks["dist"])
        }
    }
}
